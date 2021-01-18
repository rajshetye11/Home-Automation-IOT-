#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

char auth[] = "mIC3c7wck9pq4xuSjAOubJvMfsaxH1TW";

char ssid[] = "vivo 1804";
char pass[] = "7021816189";


WidgetLED led1(V0);
BlynkTimer timer;
const int Device_1 = D7;  
const int Device_2 = D6;     

int Device_1_State = 0;
int Device_2_State = 0;

String Data;
void blinkLedWidget()
{
  if (led1.getValue()) 
  {
    led1.off();
    Serial.println("LED on V1: off");
  } else {
    led1.on();
    Serial.println("LED on V1: on");
  }

  
}
BLYNK_WRITE(V1)// A
{
  Data="";
  Serial.print("Device 1"); 
  Serial.println(param.asStr()); 
  Data=(param.asStr());
  Serial.print("Data "); 
  Serial.println(Data); 
  if(Data=="0")Device_1_State=0;
  else Device_1_State=1;        
}

BLYNK_WRITE(V2)// A
{
  Data="";
  Serial.print("Device 2"); 
  Serial.println(param.asStr()); 
  Data=(param.asStr());
  Serial.print("Data "); 
  Serial.println(Data); 
  if(Data=="0")Device_2_State=0;
  else Device_2_State=1;        
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  
  Serial.println("Shri Zero@3327...");
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IOT Based Home");  
  lcd.setCursor(0, 1);
  lcd.print("Automation System");
  delay(5000);
  pinMode(Device_1, OUTPUT);  
  pinMode(Device_2, OUTPUT); 
  digitalWrite(Device_1, HIGH); 
  digitalWrite(Device_2, HIGH); 
   
  Blynk.begin(auth, ssid, pass);
  
  timer.setInterval(1000L, blinkLedWidget);
  
}

void loop()
{
  Blynk.run();
  timer.run();
  lcd.setCursor(0, 0);
  if(Device_1_State==0)
  {
   lcd.print("Light Off      "); 
    digitalWrite(Device_1, HIGH); 
  }
  if(Device_1_State==1)
  {
    lcd.print("Lights On      "); 
    digitalWrite(Device_1, LOW); 
  }
  
  lcd.setCursor(0, 1);
  if(Device_2_State==0)
  {
   lcd.print("Devices 2 Off    "); 
    digitalWrite(Device_2, HIGH); 
  }
  if(Device_2_State==1)
  {
    lcd.print("Device 2 On    "); 
    digitalWrite(Device_2, LOW); 
  }
  
}
