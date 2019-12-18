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
struct gpio_chip {int dummy; } ;
struct bcma_drv_cc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcma_chipco_gpio_pullup (struct bcma_drv_cc*,int,int /*<<< orphan*/ ) ; 
 struct bcma_drv_cc* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static void bcma_gpio_free(struct gpio_chip *chip, unsigned gpio)
{
	struct bcma_drv_cc *cc = gpiochip_get_data(chip);

	/* clear pullup */
	bcma_chipco_gpio_pullup(cc, 1 << gpio, 0);
}