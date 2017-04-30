#include <Wire.h>
#include <LiquidCrystal_I2C.h>



#define BACKLIGHT_PIN     13

LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7); // Set the LCD I2C address

//LiquidCrystal_I2C lcd(0x38, BACKLIGHT_PIN, POSITIVE);  // Set the LCD I2C address


//------------SET TeamName -------------
String teamA_name = "LAL";
String teamB_name = "GSW";

int i = 0;

int minute_1;
int minute_2;
int minute;

int second_1;
int second_2;
int second;

int score_A = 0;
int score_B = 0;

char start;
char sign;




//Set Initialize
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);              // initialize the lcd
  // Switch on the backlight


  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH);

  lcd.clear();

  lcd.home ();
}

//---------------Begin of the LOOP---------------
void loop()
{

  //-----------Begin--------------
  lcd.clear();

  //--------TeamA Name------
  lcd.setCursor(1, 1);
  lcd.print(teamA_name);

  //--------TeamB Name-------
  lcd.setCursor(13, 1);
  lcd.print(teamB_name);


  //--------MINUTE Print---------
  //------If Min < 10-------
  if (minute < 10)
  {
    lcd.setCursor(6, 0);
    lcd.print("0");
    lcd.setCursor(7, 0);
    lcd.print(minute);
  }

    //--------If 10<= MIN <= 100-------
    else if ((minute >= 10) && (minute < 100))
      {
        lcd.setCursor(6, 0);
        lcd.print(minute);
      }

  //------------- : -------------
  lcd.setCursor(8, 0);
  lcd.print(":");

  //-----------SECOND Print-------------
  if (second < 10)
  {
    lcd.setCursor(9, 0);
    lcd.print("0");
    lcd.setCursor(10, 0);
    lcd.print(second);
  }

    else if ((second >= 10) && (second < 100))
      {
        lcd.setCursor(9, 0);
        lcd.print(second);
      }



  //----------------Score A Display-------
  if (score_A < 10)
  {
    lcd.setCursor(7, 1);
    lcd.print(score_A);
  }

    else if ((score_A >= 10) && (score_A < 100))
      {
        lcd.setCursor(6, 1);
        lcd.print(score_A);
      }

    else
      if (score_A >= 100)
        {
          lcd.setCursor(5, 1);
          lcd.print(score_A);
        }

  //------------ - ----------
  lcd.setCursor(8, 1);
  lcd.print("-");

  //---------------Score B Display ---------
  lcd.setCursor(9, 1);
  lcd.print(score_B);

  //gerdataBT




  //Start of Control

  //--------------STAGE 1 : SET INITIAL MINUTE----------
  if ((i == 0) && (Serial.available() > 0))
  {

    //--------RECEIVE 1 byte of MIN--------
    if(Serial.available() == 1) {
    minute = Serial.read();
    minute = minute -48;
    } 

    //-------RECEIVE 2 bytes of MIN--------
    else
      if(Serial.available() > 1)
        {
          minute_1 = Serial.read();
          minute_2 = Serial.read();

          minute_1 = minute_1 - 48;
          minute_2 = minute_2 - 48;

          minute = minute_1*10 + minute_2;
      
        }

     //----------Print MINUTE--------
     if (minute < 10)
        {
          lcd.setCursor(6, 0);
          lcd.print("0");
          lcd.setCursor(7, 0);
          lcd.print(minute);
        }

      else if ((minute >= 10) && (minute < 100))
        {
          lcd.setCursor(6, 0);
          lcd.print(minute);
          }
    
        
      i = i + 1; //Change from Stage 1 to Stage 2
      
  } //End of i=1-------------

  
  else
    //--------------STAGE 2 : SET INITIAL SECOND----------
    if ((i == 1) && (Serial.available() > 0))
    {

      //-------RECEIVE 1 byte of SECOND------
      if(Serial.available() == 1) {
          second = Serial.read();
          second = second -48;
      }


      //------RECEIVE 2 byte of SECOND------
      else
        if(Serial.available() > 1)
          {
            second_1 = Serial.read();
            second_2 = Serial.read();

            second_1 = second_1 - 48;
            second_2 = second_2 - 48;

            second = second_1*10 + second_2;
          }

      
      //------------ Print SECOND ----------- 
      if (second < 10)
        {
          lcd.setCursor(9, 0);
          lcd.print("0");
          lcd.setCursor(10, 0);
          lcd.print(second);
        }

      else 
          if ((second >= 10) && (second < 100))
            {
              lcd.setCursor(9, 0);
              lcd.print(second);
            }

      i = i + 1;
    } //End of STAGE 2-----------------
    

    else
      //-----------------STAGE 3 : Prepare TO BEGIN-------------
      if ((i == 2) && (Serial.available() > 0))
      {
        start = Serial.read();
        while (((minute != 0) || (second != 0)) && (start == '1'))
        {
          if ((second == 0) && (minute != 0))
          {
            second = 60;
            minute = minute - 1;

            

            if (minute < 10)
            {
              lcd.setCursor(6, 0);
              lcd.print("0");
              lcd.setCursor(7, 0);
              lcd.print(minute);
            }

            else if ((minute >= 10) && (minute < 100))
            {
              lcd.setCursor(6, 0);
              lcd.print(minute);
            }

          }

          if (second > 0)
          {
            second = second - 1;

           
            if (second < 10)
            {

              lcd.setCursor(9, 0);
              lcd.print("0");
              lcd.setCursor(10, 0);
              lcd.print(second);
            }

            else if ((second >= 10) && (second < 100))
            {
              lcd.setCursor(9, 0);
              lcd.print(second);
            }

            delay(950);
          }

          sign = Serial.read();

          //----------------PLUS A----------------
          if (sign == '2')
          {
            score_A = score_A + 1;

             if (score_A < 10)
              {
                lcd.setCursor(7, 1);
                lcd.print(score_A);
              }

            else 
              if ((score_A >= 10) && (score_A < 100))
                {
                  lcd.setCursor(6, 1);
                  lcd.print(score_A);
                }


            else
              if (score_A >= 100)
                {
                  lcd.setCursor(5, 1);
                  lcd.print(score_A);
                }
         }

          else
            //----------------MINUS A----------------
            if (sign == '3')
            {
              if (score_A > 0) {
                score_A = score_A - 1;

                if (score_A < 10)
                  {
                    lcd.setCursor(7, 1);
                    lcd.print(score_A);
                  }

                else 
                if ((score_A >= 10) && (score_A < 100))
                  {
                    lcd.setCursor(6, 1);
                    lcd.print(score_A);
                  }

                else
                if (score_A >= 100)
                  {
                    lcd.setCursor(5, 1);
                    lcd.print(score_A);
                  }

              }
            }

            else
              //----------------PLUS B----------------
              if (sign == '4')
              {
                score_B = score_B + 1;

                lcd.setCursor(9, 1);
                lcd.print(score_B);
              }

              else
                //--------------MINUS B----------------
                if (sign == '5')
                {

                  if (score_B > 0) {
                    score_B = score_B - 1;

                    lcd.setCursor(9, 1);
                    lcd.print(score_B);
                  }
                }


                else
                  //-------------PAUSE / RESUME -------------
                  if (sign == '6')
                  {

                    if (start == '1')
                      start = '0';

                    else start ='1';
                  }
        }
      }


  delay(1000);
}
