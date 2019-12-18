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
 int /*<<< orphan*/  DELAY (int) ; 
 int LSR_RXRDY ; 
 int /*<<< orphan*/  REG_DATA ; 
 int /*<<< orphan*/  REG_LSR ; 
 int oct16550_delay (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (struct mtx*) ; 
 int /*<<< orphan*/  uart_unlock (struct mtx*) ; 

__attribute__((used)) static int
oct16550_getc (struct uart_bas *bas, struct mtx *hwmtx)
{
	int c, delay;

	uart_lock(hwmtx);

	/* 1/10th the time to transmit 1 character (estimate). */
	delay = oct16550_delay(bas);

	while ((uart_getreg(bas, REG_LSR) & LSR_RXRDY) == 0) {
		uart_unlock(hwmtx);
		DELAY(delay);
		uart_lock(hwmtx);
	}

	c = uart_getreg(bas, REG_DATA);

	uart_unlock(hwmtx);

	return (c);
}