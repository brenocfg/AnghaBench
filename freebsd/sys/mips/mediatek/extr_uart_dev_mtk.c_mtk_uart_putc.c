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
 int /*<<< orphan*/  UART_LSR_REG ; 
 int UART_LSR_THRE ; 
 int /*<<< orphan*/  UART_TX_REG ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_output ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mtk_uart_putc(struct uart_bas *bas, int c)
{
	char chr;
	if (!uart_output) return;
	chr = c;
	while (!(uart_getreg(bas, UART_LSR_REG) & UART_LSR_THRE));
	uart_setreg(bas, UART_TX_REG, c);
	uart_barrier(bas);
	while (!(uart_getreg(bas, UART_LSR_REG) & UART_LSR_THRE));
}