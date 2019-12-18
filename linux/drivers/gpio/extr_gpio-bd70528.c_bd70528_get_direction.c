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
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct bd70528_gpio {TYPE_1__ chip; } ;

/* Variables and functions */
 int BD70528_GPIO_OUT_EN_MASK ; 
 int /*<<< orphan*/  GPIO_OUT_REG (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct bd70528_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int bd70528_get_direction(struct gpio_chip *chip, unsigned int offset)
{
	struct bd70528_gpio *bdgpio = gpiochip_get_data(chip);
	int val, ret;

	/* Do we need to do something to IRQs here? */
	ret = regmap_read(bdgpio->chip.regmap, GPIO_OUT_REG(offset), &val);
	if (ret) {
		dev_err(bdgpio->chip.dev, "Could not read gpio direction\n");
		return ret;
	}

	return !(val & BD70528_GPIO_OUT_EN_MASK);
}