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
struct platform_device {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP93XX_GPIO_LINE_EGPIO14 ; 
 int /*<<< orphan*/  EP93XX_SYSCON_DEVCFG_PONG ; 
 int /*<<< orphan*/  ep93xx_devcfg_clear_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 

void ep93xx_pwm_release_gpio(struct platform_device *pdev)
{
	if (pdev->id == 1) {
		gpio_direction_input(EP93XX_GPIO_LINE_EGPIO14);
		gpio_free(EP93XX_GPIO_LINE_EGPIO14);

		/* EGPIO[14] used for GPIO */
		ep93xx_devcfg_clear_bits(EP93XX_SYSCON_DEVCFG_PONG);
	}
}