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
struct da9055_gpio {int /*<<< orphan*/  da9055; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9055_REG_GPIO_MODE0_2 ; 
 int /*<<< orphan*/  da9055_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct da9055_gpio* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static void da9055_gpio_set(struct gpio_chip *gc, unsigned offset, int value)
{
	struct da9055_gpio *gpio = gpiochip_get_data(gc);

	da9055_reg_update(gpio->da9055,
			DA9055_REG_GPIO_MODE0_2,
			1 << offset,
			value << offset);
}