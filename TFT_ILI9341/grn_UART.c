#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL)))-1)

void uart_init(void)
{
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);	//Turn on RX and TX circuits RXCIE0 enables Interrupt when byte received
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);	//8-Bit Char size
	UBRR0H = (BAUD_PRESCALE >> 8);	//load upper 8-Bits of baud rate value into high byte of UBRR0H
	UBRR0L = BAUD_PRESCALE;			//load lower 8-Bits of Baud rate into low byte of UBRR0L

}
void uart_send_char(char c)
{
	while((UCSR0A & (1<<UDRE0)) == 0){};
    UDR0 = c;
}
void uart_send_string(char *s)
{
	while(*s != 0x00)
	{
		uart_send_char(*s);
		s++;
	}
}//end of send_string

void uart_send_u8data(uint8_t d)
{
	char buffer[10];
	
	itoa(d,buffer,10);
	uart_send_string(buffer);
}
void uart_send_u16data(uint16_t d)
{
	char buffer[10];
	
	utoa(d,buffer,10);
	uart_send_string(buffer);
}
/*
void uart_string_buff_reset(void)
{
	z_string_buffer = string_buffer; //Zeiger auf globbales array
}*/

