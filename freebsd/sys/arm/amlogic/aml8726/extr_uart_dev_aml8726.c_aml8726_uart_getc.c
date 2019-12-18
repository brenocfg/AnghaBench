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
 int /*<<< orphan*/  AML_UART_RFIFO_REG ; 
 int /*<<< orphan*/  AML_UART_STATUS_REG ; 
 int AML_UART_STATUS_RX_FIFO_EMPTY ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (struct mtx*) ; 
 int /*<<< orphan*/  uart_unlock (struct mtx*) ; 

__attribute__((used)) static int
aml8726_uart_getc(struct uart_bas *bas, struct mtx *hwmtx)
{
	int c;

	uart_lock(hwmtx);

	while ((uart_getreg(bas, AML_UART_STATUS_REG) &
	    AML_UART_STATUS_RX_FIFO_EMPTY) != 0) {
		uart_unlock(hwmtx);
		DELAY(4);
		uart_lock(hwmtx);
	}

	c = uart_getreg(bas, AML_UART_RFIFO_REG) & 0xff;

	uart_unlock(hwmtx);

	return (c);
}