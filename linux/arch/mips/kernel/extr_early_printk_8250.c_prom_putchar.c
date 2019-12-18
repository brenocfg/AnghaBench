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
 int /*<<< orphan*/  UART_LSR ; 
 int UART_LSR_TEMT ; 
 int UART_LSR_THRE ; 
 int /*<<< orphan*/  UART_TX ; 
 int /*<<< orphan*/  serial8250_base ; 
 unsigned int serial8250_tx_timeout ; 
 int serial_in (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (int /*<<< orphan*/ ,char) ; 

void prom_putchar(char c)
{
	unsigned int timeout;
	int status, bits;

	if (!serial8250_base)
		return;

	timeout = serial8250_tx_timeout;
	bits = UART_LSR_TEMT | UART_LSR_THRE;

	do {
		status = serial_in(UART_LSR);

		if (--timeout == 0)
			break;
	} while ((status & bits) != bits);

	if (timeout)
		serial_out(UART_TX, c);
}