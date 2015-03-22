/*

 'codesend' originally hacked from 'send' by @justy
 
 -  The provided rc_switch 'send' command uses the form systemCode, unitCode, command
    which is not suitable for our purposes.  Instead, we call 
    send(code, length); // where length is always 24 and code is simply the code
    we find using the RF_sniffer.ino Arduino sketch.

-   Added pulse length to get thsi to work with receivers that use a different pulse length
    Pulse length can be determined by running RFSniffer 

    Usage: ./codesend decimalcode pulse_length
    (Use RF_Sniffer.ino to check that RF signals are being produced by the RPi's transmitter)
 
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) {

    // This pin is not the first pin on the RPi GPIO header!
    // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
    // for more information.
    int PIN = 0;

    // Parse parameters to this command as integers
    int code = atoi(argv[1]);
    int pulse = atoi(argv[2]);

    if (wiringPiSetup () == -1) 
        return 1;
    printf("sending code[%i] pulse[%i]\n", code, pulse);
    RCSwitch mySwitch = RCSwitch();
    if (pulse > 0)
        mySwitch.setPulseLength(pulse);
    mySwitch.enableTransmit(PIN);
    mySwitch.send(code, 24);
    return 0;

}