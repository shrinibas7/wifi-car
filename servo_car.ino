      // Enable/speed motors Left         GPIO12(D6)
#define IN_1  16          // L298N in3 motors Left            GPIO2(D4)
#define IN_2  5
#define IN_3  0          // L298N in3 motors Left            GPIO2(D4)
#define IN_4  2          // L298N in4 motors Left            GPIO0(D3)

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <Servo.h>

Servo myservo; 
Servo myservo1; 

String command;             //String to store app command state.
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;

const char* ssid = "MECIK CAR";
ESP8266WebServer server(80);

void setup() {
 analogWriteFreq(50);
  myservo.attach(5); 
myservo.write(90); 

   myservo1.attach(4); 
myservo1.write(90); 
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
  
  Serial.begin(115200);
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void goAhead(){ 

  
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
     
  }

void goBack(){ 

  
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);   
      digitalWrite(IN_3,HIGH);
      digitalWrite(IN_4, LOW);
     
     
  }

void goRight(){ 

   digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);

       myservo.write(180); 
     
       myservo1.write(180);
      
  }

void goLeft(){

   digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);

        myservo.write(0); 
       
       myservo1.write(0); 
       
     
  }
  void goAheadRight(){

       
   
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, HIGH);    
       myservo.write(90); 
       
       myservo1.write(90); 
  }
   void  goAheadLeft(){

       
    digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
     
  }
void stopRobot(){  

     
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
       myservo.write(90); 
       
       myservo1.write(90); 
     
 }



void loop() {
    server.handleClient();
    
      command = server.arg("State");
      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
      else if (command == "S") stopRobot();
       else if (command == "I") goAheadRight();
      else if (command == "G") goAheadLeft();
    //  else if (command == "J") goBackRight();
     // else if (command == "H") goBackLeft();
     else{
      myservo.write(90); 
      myservo1.write(90); 
     }
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}






