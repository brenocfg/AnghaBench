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
 int /*<<< orphan*/  REG_DATA ; 
 int oct16550_delay (struct uart_bas*) ; 
 int /*<<< orphan*/  oct16550_wait_txhr_empty (struct uart_bas*,int,int) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
oct16550_putc (struct uart_bas *bas, int c)
{
	int delay;

	/* 1/10th the time to transmit 1 character (estimate). */
	delay = oct16550_delay(bas);
        oct16550_wait_txhr_empty(bas, 100, delay);
	uart_setreg(bas, REG_DATA, c);
	uart_barrier(bas);
        oct16550_wait_txhr_empty(bas, 100, delay);
}