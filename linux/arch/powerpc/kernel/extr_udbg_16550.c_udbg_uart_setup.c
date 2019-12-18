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

/* Variables and functions */
 int LCR_DLAB ; 
 int /*<<< orphan*/  UART_DLL ; 
 int /*<<< orphan*/  UART_DLM ; 
 int /*<<< orphan*/  UART_FCR ; 
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  UART_LCR ; 
 int /*<<< orphan*/  UART_MCR ; 
 int /*<<< orphan*/  udbg_uart_out (int /*<<< orphan*/ ,int) ; 

void udbg_uart_setup(unsigned int speed, unsigned int clock)
{
	unsigned int dll, base_bauds;

	if (!udbg_uart_out)
		return;

	if (clock == 0)
		clock = 1843200;
	if (speed == 0)
		speed = 9600;

	base_bauds = clock / 16;
	dll = base_bauds / speed;

	udbg_uart_out(UART_LCR, 0x00);
	udbg_uart_out(UART_IER, 0xff);
	udbg_uart_out(UART_IER, 0x00);
	udbg_uart_out(UART_LCR, LCR_DLAB);
	udbg_uart_out(UART_DLL, dll & 0xff);
	udbg_uart_out(UART_DLM, dll >> 8);
	/* 8 data, 1 stop, no parity */
	udbg_uart_out(UART_LCR, 0x3);
	/* RTS/DTR */
	udbg_uart_out(UART_MCR, 0x3);
	/* Clear & enable FIFOs */
	udbg_uart_out(UART_FCR, 0x7);
}