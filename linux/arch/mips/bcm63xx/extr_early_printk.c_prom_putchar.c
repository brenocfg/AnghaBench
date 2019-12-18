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
 int /*<<< orphan*/  UART_FIFO_REG ; 
 int /*<<< orphan*/  bcm_uart0_writel (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_xfered () ; 

void prom_putchar(char c)
{
	wait_xfered();
	bcm_uart0_writel(c, UART_FIFO_REG);
	wait_xfered();
}