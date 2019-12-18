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
 int /*<<< orphan*/  AR5315_GPIO_PINS ; 
 int /*<<< orphan*/  AR5315_SYSREG_GPIO_CR ; 
 int /*<<< orphan*/  AR5315_SYSREG_GPIO_DI ; 
 int /*<<< orphan*/  AR5315_SYSREG_GPIO_DO ; 
 int /*<<< orphan*/  AR5315_SYSREG_WDOG_CTL ; 
 int /*<<< orphan*/  AR5315_SYSREG_WDOG_TIMER ; 
 int /*<<< orphan*/  AR5315_UART_BASE ; 
 int /*<<< orphan*/  MIPS_PHYS_TO_KSEG1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u_ar531x_gpio_cr ; 
 int /*<<< orphan*/  u_ar531x_gpio_di ; 
 int /*<<< orphan*/  u_ar531x_gpio_do ; 
 int /*<<< orphan*/  u_ar531x_gpio_pins ; 
 int /*<<< orphan*/  u_ar531x_uart_addr ; 
 int /*<<< orphan*/  u_ar531x_wdog_ctl ; 
 int /*<<< orphan*/  u_ar531x_wdog_timer ; 

__attribute__((used)) static void
ar5315_chip_soc_init(void)
{
	u_ar531x_uart_addr = MIPS_PHYS_TO_KSEG1(AR5315_UART_BASE);

	u_ar531x_gpio_di = AR5315_SYSREG_GPIO_DI;
	u_ar531x_gpio_do = AR5315_SYSREG_GPIO_DO;
	u_ar531x_gpio_cr = AR5315_SYSREG_GPIO_CR;
	u_ar531x_gpio_pins = AR5315_GPIO_PINS;

	u_ar531x_wdog_ctl = AR5315_SYSREG_WDOG_CTL;
	u_ar531x_wdog_timer = AR5315_SYSREG_WDOG_TIMER;
}