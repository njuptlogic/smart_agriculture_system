#include <Wire.h>
#include"dht11.h"
#include "LiquidCrystal_I2C.h"
#include <Adafruit_NeoPixel.h>    //引入头文件

#define LED_Pin         5  //定义信号输出引脚
#define  PIXEL_COUNT    12   //定义LED灯个数

#define    DHT11PIN     8
int motor=6;
int analogPin=A0;
int WaterPumpPin=7;
int count=12;
Adafruit_NeoPixel pixels(PIXEL_COUNT, LED_Pin, NEO_GRB + NEO_KHZ800);

float i=0;
float j=0;
dht11 DHT11; 
int  ADPIN  = A1  ;
int  value = 0 ;
float voltage = 0.0 ;
LiquidCrystal_I2C lcd(0x27, 16, 2);// 0x27 is the I2C bus address for an unmodified backpack
void setup() {
  pinMode(DHT11PIN, OUTPUT);
  pinMode(motor,OUTPUT);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  lcd.init(); 
  lcd.backlight();
  pinMode(analogPin,INPUT);
  pinMode(WaterPumpPin,OUTPUT);
  digitalWrite(WaterPumpPin,LOW);
  Serial.begin(9600);
  pixels.begin();           
  pixels.show();
  pixels.setBrightness(30);
  
  pinMode(LED_Pin,OUTPUT);
  pinMode(ADPIN,INPUT);
  Serial.begin(9600);    //Serial Baud rate is 9600
}

void loop() {
  int chk = DHT11.read(DHT11PIN);
  lcd.setCursor(0, 0);
  lcd.print("Tep: ");
  lcd.print((float)DHT11.temperature, 2);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print((float)DHT11.humidity, 2);
  lcd.print("%");
  delay(400);
  if(DHT11.temperature>29)
    {
      digitalWrite(motor,HIGH);
     }
     else
     {
       digitalWrite(motor,LOW);
      }       
      float data=analogRead(analogPin);
    Serial.println(data);
    i=data/1023;
    j=i*100;
    lcd.setCursor(0, 0);
    lcd.print("The hum is: ");
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print((float)j, 2);
    lcd.print("%");
    delay(400);
    if(data<220)
    {
      digitalWrite(WaterPumpPin,HIGH);
     }
     else
     {
       digitalWrite(WaterPumpPin,LOW);
      }
    value =  analogRead(ADPIN);
    voltage = ( ( float )value )/1023 ;
    value = (int)(voltage * 256) ;  //convert voltage to value
    Serial.println(value );
    analogWrite(LED_Pin,1/value);
    delay(100);
}
