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
 int /*<<< orphan*/  AR724X_GPIO_FUNC_JTAG_DISABLE ; 
 int /*<<< orphan*/  AR724X_GPIO_FUNC_SPI_EN ; 
 int /*<<< orphan*/  RB750_LVC573_LE ; 
 int /*<<< orphan*/  ath79_gpio_function_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb750_latch_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rb750_nand_disable_pins(void)
{
	ath79_gpio_function_setup(AR724X_GPIO_FUNC_SPI_EN,
				  AR724X_GPIO_FUNC_JTAG_DISABLE);
	rb750_latch_change(0, RB750_LVC573_LE);
}