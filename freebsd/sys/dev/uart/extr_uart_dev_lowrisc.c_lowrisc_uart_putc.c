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
 int DR_TX_FIFO_FULL ; 
 int GETREG (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETREG (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UART_DR ; 

__attribute__((used)) static void
lowrisc_uart_putc(struct uart_bas *bas, int c)
{

	while (GETREG(bas, UART_DR) & DR_TX_FIFO_FULL)
		;

	SETREG(bas, UART_DR, c);
}