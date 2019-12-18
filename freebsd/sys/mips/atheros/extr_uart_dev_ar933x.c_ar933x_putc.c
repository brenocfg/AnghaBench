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
struct uart_bas {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR933X_UART_DATA_REG ; 
 int AR933X_UART_DATA_TX_CSR ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ar933x_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar933x_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar933x_putc(struct uart_bas *bas, int c)
{
	int limit;

	limit = 250000;

	/* Wait for space in the TX FIFO */
	while ( ((ar933x_getreg(bas, AR933X_UART_DATA_REG) &
	    AR933X_UART_DATA_TX_CSR) == 0) && --limit)
		DELAY(4);

	/* Write the actual byte */
	ar933x_setreg(bas, AR933X_UART_DATA_REG,
	    (c & 0xff) | AR933X_UART_DATA_TX_CSR);
}