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
 int /*<<< orphan*/  CONFIG_SOC_MT7621 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int UART_LSR_THRE ; 
 int /*<<< orphan*/  UART_REG_LSR ; 
 int /*<<< orphan*/  UART_REG_LSR_RT2880 ; 
 int /*<<< orphan*/  UART_REG_TX ; 
 int /*<<< orphan*/  UART_TX ; 
 int /*<<< orphan*/  find_uart_base () ; 
 int init_complete ; 
 scalar_t__ soc_is_mt7628 () ; 
 int uart_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_w32 (unsigned char,int /*<<< orphan*/ ) ; 

void prom_putchar(char ch)
{
	if (!init_complete) {
		find_uart_base();
		init_complete = 1;
	}

	if (IS_ENABLED(CONFIG_SOC_MT7621) || soc_is_mt7628()) {
		uart_w32((unsigned char)ch, UART_TX);
		while ((uart_r32(UART_REG_LSR) & UART_LSR_THRE) == 0)
			;
	} else {
		while ((uart_r32(UART_REG_LSR_RT2880) & UART_LSR_THRE) == 0)
			;
		uart_w32((unsigned char)ch, UART_REG_TX);
		while ((uart_r32(UART_REG_LSR_RT2880) & UART_LSR_THRE) == 0)
			;
	}
}