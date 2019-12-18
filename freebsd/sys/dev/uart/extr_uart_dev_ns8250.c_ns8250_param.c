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
typedef  int uint8_t ;
struct uart_bas {int /*<<< orphan*/  rclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int LCR_5BITS ; 
 int LCR_6BITS ; 
 int LCR_7BITS ; 
 int LCR_8BITS ; 
 int LCR_DLAB ; 
 int LCR_STOPB ; 
 int /*<<< orphan*/  REG_DLH ; 
 int /*<<< orphan*/  REG_DLL ; 
 int /*<<< orphan*/  REG_LCR ; 
 int ns8250_divisor (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ns8250_param(struct uart_bas *bas, int baudrate, int databits, int stopbits,
    int parity)
{
	int divisor;
	uint8_t lcr;

	lcr = 0;
	if (databits >= 8)
		lcr |= LCR_8BITS;
	else if (databits == 7)
		lcr |= LCR_7BITS;
	else if (databits == 6)
		lcr |= LCR_6BITS;
	else
		lcr |= LCR_5BITS;
	if (stopbits > 1)
		lcr |= LCR_STOPB;
	lcr |= parity << 3;

	/* Set baudrate. */
	if (baudrate > 0) {
		divisor = ns8250_divisor(bas->rclk, baudrate);
		if (divisor == 0)
			return (EINVAL);
		uart_setreg(bas, REG_LCR, lcr | LCR_DLAB);
		uart_barrier(bas);
		uart_setreg(bas, REG_DLL, divisor & 0xff);
		uart_setreg(bas, REG_DLH, (divisor >> 8) & 0xff);
		uart_barrier(bas);
	}

	/* Set LCR and clear DLAB. */
	uart_setreg(bas, REG_LCR, lcr);
	uart_barrier(bas);
	return (0);
}