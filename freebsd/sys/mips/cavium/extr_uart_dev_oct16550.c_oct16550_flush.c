#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct uart_bas {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCR_ENABLE ; 
 int /*<<< orphan*/  FCR_RCV_RST ; 
 int /*<<< orphan*/  FCR_XMT_RST ; 
 int /*<<< orphan*/  REG_FCR ; 
 int UART_FLUSH_RECEIVER ; 
 int UART_FLUSH_TRANSMITTER ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
oct16550_flush (struct uart_bas *bas, int what)
{
	uint8_t fcr;

	fcr = FCR_ENABLE;
	if (what & UART_FLUSH_TRANSMITTER)
		fcr |= FCR_XMT_RST;
	if (what & UART_FLUSH_RECEIVER)
		fcr |= FCR_RCV_RST;
	uart_setreg(bas, REG_FCR, fcr);
	uart_barrier(bas);
}