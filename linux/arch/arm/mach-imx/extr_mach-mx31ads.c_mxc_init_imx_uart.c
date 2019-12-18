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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx31_add_imx_uart0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxc_iomux_setup_multiple_pins (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uart_pdata ; 
 int /*<<< orphan*/  uart_pins ; 

__attribute__((used)) static inline void mxc_init_imx_uart(void)
{
	mxc_iomux_setup_multiple_pins(uart_pins, ARRAY_SIZE(uart_pins), "uart-0");
	imx31_add_imx_uart0(&uart_pdata);
}