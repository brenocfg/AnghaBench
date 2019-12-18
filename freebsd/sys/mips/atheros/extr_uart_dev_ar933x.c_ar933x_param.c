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
typedef  int uint32_t ;
struct uart_bas {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR933X_UART_CLOCK_REG ; 
 int AR933X_UART_CLOCK_SCALE_M ; 
 int AR933X_UART_CLOCK_SCALE_S ; 
 int AR933X_UART_CLOCK_STEP_M ; 
 int /*<<< orphan*/  ar933x_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar933x_uart_get_scale_step (struct uart_bas*,int,int*,int*) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 

__attribute__((used)) static int
ar933x_param(struct uart_bas *bas, int baudrate, int databits, int stopbits,
    int parity)
{
	/* UART always 8 bits */

	/* UART always 1 stop bit */

	/* UART parity is controllable by bits 0:1, ignore for now */

	/* Set baudrate if required. */
	if (baudrate > 0) {
		uint32_t clock_scale, clock_step;

		/* Find the best fit for the given baud rate */
		ar933x_uart_get_scale_step(bas, baudrate, &clock_scale,
		    &clock_step);

		/*
		 * Program the clock register in its entirety - no need
		 * for Read-Modify-Write.
		 */
		ar933x_setreg(bas, AR933X_UART_CLOCK_REG,
		    ((clock_scale & AR933X_UART_CLOCK_SCALE_M)
		      << AR933X_UART_CLOCK_SCALE_S) |
		    (clock_step & AR933X_UART_CLOCK_STEP_M));
	}

	uart_barrier(bas);
	return (0);
}