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
 int LSR_DR ; 
 int /*<<< orphan*/  UART_LSR ; 
 int /*<<< orphan*/  UART_RBR ; 
 int udbg_uart_in (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udbg_uart_getc_poll(void)
{
	if (!udbg_uart_in)
		return -1;

	if (!(udbg_uart_in(UART_LSR) & LSR_DR))
		return udbg_uart_in(UART_RBR);

	return -1;
}