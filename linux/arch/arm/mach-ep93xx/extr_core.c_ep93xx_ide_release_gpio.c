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
 int /*<<< orphan*/  EP93XX_GPIO_LINE_E (int) ; 
 int /*<<< orphan*/  EP93XX_GPIO_LINE_EGPIO15 ; 
 int /*<<< orphan*/  EP93XX_GPIO_LINE_EGPIO2 ; 
 int /*<<< orphan*/  EP93XX_GPIO_LINE_G (int) ; 
 int /*<<< orphan*/  EP93XX_GPIO_LINE_H (int) ; 
 int EP93XX_SYSCON_DEVCFG_EONIDE ; 
 int EP93XX_SYSCON_DEVCFG_GONIDE ; 
 int EP93XX_SYSCON_DEVCFG_HONIDE ; 
 int /*<<< orphan*/  ep93xx_devcfg_set_bits (int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 

void ep93xx_ide_release_gpio(struct platform_device *pdev)
{
	int i;

	for (i = 2; i < 8; i++)
		gpio_free(EP93XX_GPIO_LINE_E(i));
	for (i = 4; i < 8; i++)
		gpio_free(EP93XX_GPIO_LINE_G(i));
	for (i = 0; i < 8; i++)
		gpio_free(EP93XX_GPIO_LINE_H(i));
	gpio_free(EP93XX_GPIO_LINE_EGPIO15);
	gpio_free(EP93XX_GPIO_LINE_EGPIO2);


	/* GPIO ports E[7:2], G[7:4] and H used by GPIO */
	ep93xx_devcfg_set_bits(EP93XX_SYSCON_DEVCFG_EONIDE |
			       EP93XX_SYSCON_DEVCFG_GONIDE |
			       EP93XX_SYSCON_DEVCFG_HONIDE);
}