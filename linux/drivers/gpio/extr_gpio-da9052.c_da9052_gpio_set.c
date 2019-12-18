#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gpio_chip {int dummy; } ;
struct da9052_gpio {TYPE_1__* da9052; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DA9052_GPIO_0_1_REG ; 
 int /*<<< orphan*/  DA9052_GPIO_EVEN_PORT_MODE ; 
 int DA9052_GPIO_EVEN_SHIFT ; 
 int /*<<< orphan*/  DA9052_GPIO_ODD_PORT_MODE ; 
 int DA9052_GPIO_ODD_SHIFT ; 
 scalar_t__ da9052_gpio_port_odd (unsigned int) ; 
 int da9052_reg_update (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct da9052_gpio* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static void da9052_gpio_set(struct gpio_chip *gc, unsigned offset, int value)
{
	struct da9052_gpio *gpio = gpiochip_get_data(gc);
	int ret;

	if (da9052_gpio_port_odd(offset)) {
			ret = da9052_reg_update(gpio->da9052, (offset >> 1) +
						DA9052_GPIO_0_1_REG,
						DA9052_GPIO_ODD_PORT_MODE,
						value << DA9052_GPIO_ODD_SHIFT);
			if (ret != 0)
				dev_err(gpio->da9052->dev,
					"Failed to updated gpio odd reg,%d",
					ret);
	} else {
			ret = da9052_reg_update(gpio->da9052, (offset >> 1) +
						DA9052_GPIO_0_1_REG,
						DA9052_GPIO_EVEN_PORT_MODE,
						value << DA9052_GPIO_EVEN_SHIFT);
			if (ret != 0)
				dev_err(gpio->da9052->dev,
					"Failed to updated gpio even reg,%d",
					ret);
	}
}