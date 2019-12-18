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
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR933X_UART_DATA_REG ; 
 int AR933X_UART_DATA_RX_CSR ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ar933x_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar933x_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_lock (struct mtx*) ; 
 int /*<<< orphan*/  uart_unlock (struct mtx*) ; 

__attribute__((used)) static int
ar933x_getc(struct uart_bas *bas, struct mtx *hwmtx)
{
	int c;

	uart_lock(hwmtx);

	/* Wait for a character to come ready */
	while ((ar933x_getreg(bas, AR933X_UART_DATA_REG) &
	    AR933X_UART_DATA_RX_CSR) == 0) {
		uart_unlock(hwmtx);
		DELAY(4);
		uart_lock(hwmtx);
	}

	/* Read the top of the RX FIFO */
	c = ar933x_getreg(bas, AR933X_UART_DATA_REG) & 0xff;

	/* Remove that entry from said RX FIFO */
	ar933x_setreg(bas, AR933X_UART_DATA_REG, AR933X_UART_DATA_RX_CSR);

	uart_unlock(hwmtx);

	return (c);
}