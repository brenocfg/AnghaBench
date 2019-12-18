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

/* Variables and functions */
 int /*<<< orphan*/  UART_THR ; 
 int /*<<< orphan*/  udbg_uart_flush () ; 
 int /*<<< orphan*/  udbg_uart_out (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void udbg_uart_putc(char c)
{
	if (!udbg_uart_out)
		return;

	if (c == '\n')
		udbg_uart_putc('\r');
	udbg_uart_flush();
	udbg_uart_out(UART_THR, c);
}