/*
 * main.c
 *
 *  Created on: Sep 24, 2023
 *      Author: hp
 */
#include "STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "GIE.h"
#include "TIMER_TEST_interface.h"
#include "avr/interrupt.h"
#include"util/delay.h"
#include<avr/io.h>
 u8 res=0,seccount=0;
u8 value,trynum;


int main()
{
	//LCD
	  DIO_u8SetPortDir(DIO_PORTA, DIO_PORT_OUT);
	  DIO_u8SetPortDir(DIO_PORTB, 0x03);
		//kpd
		DIO_u8SetPortDir(DIO_PORTC, 0b00000111);
		DIO_u8SetPortValue(DIO_PORTC, 0xff);
		CLCD_voidInit();
		//timer
		TIMER0_voidOfInit();
		TIMER0_voidPreLoadValue(192);
		GIE_voidEnable();

u16    arrnum[]={3,5,1,1,0,1,5,4,8,6};
u16 arrresult[]={6,5,8,7,4,9,9,7,10,13};
while(1)
	{

		for(u8 i=0;i<10;i++){
			CLCD_voidWriteNumber(arrnum[i]);
			CLCD_voidSendString("+");
			CLCD_voidGoToXY(0,3);
			CLCD_voidSendString("=");
			CLCD_voidWriteNumber(arrresult[i]);
		do{
			 value = KPD_u8GetPressedKey();
		}while(value==0xff);
		trynum=(value+arrnum[i]);
		CLCD_voidGoToXY(0,2);
		CLCD_voidWriteNumber(value);
		_delay_ms(500);
		if(trynum==arrresult[i])
		{
			res++;
			CLCD_voidSendCommand(0x01);
			CLCD_voidGoToXY(0,0);
			CLCD_voidSendString("PRAVOO");
			_delay_ms(250);
			CLCD_voidSendCommand(0x01);
		}
		else
		{
			CLCD_voidSendCommand(0x01);
		    CLCD_voidGoToXY(0,0);
		    CLCD_voidSendString("ohh no");
		    _delay_ms(250);
		   CLCD_voidSendCommand(0x01);
		}

		}
		CLCD_voidSendCommand(0x01);
				CLCD_voidGoToXY(0,0);
			    CLCD_voidSendString("good work ^-*");
			    CLCD_voidGoToXY(1,0);
			    CLCD_voidWriteNumber(res);
			    CLCD_voidGoToXY(1,2);
			    CLCD_voidSendString("points!");
			    _delay_ms(1000);
			    while(res!=0);
	}
return 0;
}
ISR(TIMER0_OVF_vect)
{
	static u16 c=0;
	c++;
	if(c==39070){

		TCNT0=192;
	    seccount++;
	    c=0;
	    if(value==0xff)
	    {

	        CLCD_voidGoToXY(1,5);
	    	CLCD_voidSendString("hurry!!!");
	    	_delay_ms(500);
	    }
	}
}
