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
struct uart_bas {int dummy; } ;

/* Variables and functions */
 int MCR_DTR ; 
 int MCR_RTS ; 
 int /*<<< orphan*/  REG_IER ; 
 int /*<<< orphan*/  REG_MCR ; 
 int /*<<< orphan*/  oct16550_clrint (struct uart_bas*) ; 
 int /*<<< orphan*/  oct16550_param (struct uart_bas*,int,int,int,int) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
oct16550_init (struct uart_bas *bas, int baudrate, int databits, int stopbits,
    int parity)
{
	u_char	ier;

	oct16550_param(bas, baudrate, databits, stopbits, parity);

	/* Disable all interrupt sources. */
	ier = uart_getreg(bas, REG_IER) & 0x0;
	uart_setreg(bas, REG_IER, ier);
	uart_barrier(bas);

	/* Disable the FIFO (if present). */
//	uart_setreg(bas, REG_FCR, 0);
	uart_barrier(bas);

	/* Set RTS & DTR. */
	uart_setreg(bas, REG_MCR, MCR_RTS | MCR_DTR);
	uart_barrier(bas);

	oct16550_clrint(bas);
}