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
 int STAT_TX_FIFO_FULL ; 
 int /*<<< orphan*/  UART_STAT ; 
 int /*<<< orphan*/  UART_TSH ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
uart_mvebu_putc(struct uart_bas *bas, int c)
{
	while (uart_getreg(bas, UART_STAT) & STAT_TX_FIFO_FULL)
		;
	uart_setreg(bas, UART_TSH, c & 0xff);
}