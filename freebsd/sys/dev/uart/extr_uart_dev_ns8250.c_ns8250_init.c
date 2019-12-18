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
typedef  int u_char ;
struct uart_bas {scalar_t__ rclk; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_RCLK ; 
 int FCR_UART_ON ; 
 int MCR_DTR ; 
 int MCR_IE ; 
 int MCR_RTS ; 
 int /*<<< orphan*/  REG_FCR ; 
 int /*<<< orphan*/  REG_IER ; 
 int /*<<< orphan*/  REG_MCR ; 
 int /*<<< orphan*/  ns8250_clrint (struct uart_bas*) ; 
 int /*<<< orphan*/  ns8250_param (struct uart_bas*,int,int,int,int) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ns8250_init(struct uart_bas *bas, int baudrate, int databits, int stopbits,
    int parity)
{
	u_char ier, val;

	if (bas->rclk == 0)
		bas->rclk = DEFAULT_RCLK;
	ns8250_param(bas, baudrate, databits, stopbits, parity);

	/* Disable all interrupt sources. */
	/*
	 * We use 0xe0 instead of 0xf0 as the mask because the XScale PXA
	 * UARTs split the receive time-out interrupt bit out separately as
	 * 0x10.  This gets handled by ier_mask and ier_rxbits below.
	 */
	ier = uart_getreg(bas, REG_IER) & 0xe0;
	uart_setreg(bas, REG_IER, ier);
	uart_barrier(bas);

	/* Disable the FIFO (if present). */
	val = 0;
#ifdef CPU_XBURST
	val |= FCR_UART_ON;
#endif
	uart_setreg(bas, REG_FCR, val);
	uart_barrier(bas);

	/* Set RTS & DTR. */
	uart_setreg(bas, REG_MCR, MCR_IE | MCR_RTS | MCR_DTR);
	uart_barrier(bas);

	ns8250_clrint(bas);
}