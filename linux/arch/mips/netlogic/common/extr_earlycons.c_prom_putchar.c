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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETLOGIC_IO_UART_0_OFFSET ; 
 int /*<<< orphan*/  UART_LSR ; 
 int UART_LSR_THRE ; 
 int /*<<< orphan*/  UART_TX ; 
 int /*<<< orphan*/  nlm_get_uart_regbase (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_mmio_base (int /*<<< orphan*/ ) ; 
 int nlm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 

void prom_putchar(char c)
{
	uint64_t uartbase;

#if defined(CONFIG_CPU_XLP)
	uartbase = nlm_get_uart_regbase(0, 0);
#elif defined(CONFIG_CPU_XLR)
	uartbase = nlm_mmio_base(NETLOGIC_IO_UART_0_OFFSET);
#endif
	while ((nlm_read_reg(uartbase, UART_LSR) & UART_LSR_THRE) == 0)
		;
	nlm_write_reg(uartbase, UART_TX, c);
}