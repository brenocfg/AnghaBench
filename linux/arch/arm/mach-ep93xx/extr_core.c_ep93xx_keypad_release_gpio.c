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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP93XX_GPIO_LINE_C (int) ; 
 int /*<<< orphan*/  EP93XX_GPIO_LINE_D (int) ; 
 int EP93XX_SYSCON_DEVCFG_GONK ; 
 int EP93XX_SYSCON_DEVCFG_KEYS ; 
 int /*<<< orphan*/  ep93xx_devcfg_set_bits (int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 

void ep93xx_keypad_release_gpio(struct platform_device *pdev)
{
	int i;

	for (i = 0; i < 8; i++) {
		gpio_free(EP93XX_GPIO_LINE_C(i));
		gpio_free(EP93XX_GPIO_LINE_D(i));
	}

	/* Disable the keypad controller; GPIO ports C and D used for GPIO */
	ep93xx_devcfg_set_bits(EP93XX_SYSCON_DEVCFG_KEYS |
			       EP93XX_SYSCON_DEVCFG_GONK);
}