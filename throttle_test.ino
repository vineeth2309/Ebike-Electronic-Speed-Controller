#include <LiquidCrystal.h>

//PINS USED
int throttle_pin = A0;
int cruise_control = 2;
int hall=8;
int motor_driver=3;
const int d4 = 4, d5 = 5, d6 = 6, d7 = 7, rs = 11, en = 12;
int battery = A1;
   
//

float duration;
float duration1;
float velocity;
int set1=0;
int set2=0;
int value=0;
int value1=0;
int value2=0;
float vout = 0.0;


//LCD SETUP
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//

void setup() 
{
  lcd.begin(16, 2);
  lcd.print("BOOTING....");
  pinMode(throttle_pin,INPUT);
  pinMode(motor_driver,OUTPUT);
  pinMode(cruise_control,INPUT);
  pinMode(hall,INPUT);
  pinMode(battery,INPUT);
  digitalWrite(cruise_control,LOW);
  Serial.begin(9600);
  delay(1000);
  lcd.clear();
}

void loop() {
 
  while(1)
  {   
    lcd.setCursor(0, 0);

    /////// NORMAL CONTROL//////
    
    if(set1==0)
    {
      value=analogRead(throttle_pin);
      value=map(value,170,880,0,255);
      //TO SMOOTHEN THE THROTTLE READING AND REMOVE SLIGHT READINGS
      if(value<=10)
      {
       value=0;
      }
      /////
   
      Serial.println(value);  
      if(value>=0&&value<255)
      {
        analogWrite(motor_driver,value);
        lcd.print(value);
        //lcd.print("1.1");        
        delay(100);
      }
        
    }
    ////////

    ///////////CRUISE CONTROL////////////////
    value2=digitalRead(cruise_control);
    delay(100);
    //Serial.println(value2);
 
    if(value2==HIGH)
    {
      
      value1=value;
      //Serial.println(value2);
      delay(200);
      if(value1>=30&&value1<255)
      {
        set1=set1+1; 
        
      }
      else
      {
        set1=0;
      }
      Serial.println("SET1: ");
      Serial.println(set1);      
    }
    
    if(set1>=1)
    
    {
      set2=set1%2;
      if(set2==0)
      {
        set1=0;
        set2=0;
        lcd.clear();
      }
        
      if (set2!=0)
      {
        //lcd.setCursor(0,0);
        lcd.print("CRUISE MODE  ");
        lcd.print(value1);
        analogWrite(motor_driver,value1);
        Serial.println(value1);
        delay(100);
      }
        
        
    }
    else
    {
      set1=0;
      value1=0;
    }
    //END OF CRUISE CONTROL
    
    /// HALL SENSOR FOR SPEED MEASUREMENT/////   
    duration = pulseIn(hall, FALLING);
    duration=duration/1000000;
    //Serial.println(duration);
    duration1 = (1/duration);
    //duration1=duration1;
    velocity=duration1*0.3315;
    //velocity=velocity*3.6;
    lcd.setCursor(0,1);
    Serial.println(velocity);
    lcd.print("Speed: ");
    lcd.print(velocity);
    /////////////

    ////BATTERY VOLTAGE MEASUREMENT//////
    vout=analogRead(battery);
    vout=map(vout,0,1023,0,25);
    lcd.setCursor(12,2);
    lcd.print(vout);
    delay(300);
    //lcd.clear();
    /////////
  }
  
  
  // put your main code here, to run repeatedly:

}

