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
 scalar_t__ UART_FIFO_REG ; 
 int /*<<< orphan*/  WRITEREG (scalar_t__,int) ; 
 scalar_t__ uart_base ; 
 int /*<<< orphan*/  wait_xfered () ; 

void board_putc(int ch)
{
	if (!uart_base)
		return;

	wait_xfered();
        WRITEREG(uart_base + UART_FIFO_REG, ch);
	wait_xfered();
}