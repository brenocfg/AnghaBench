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
typedef  int /*<<< orphan*/  u8 ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct bd70528_gpio {TYPE_1__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD70528_GPIO_OUT_HI ; 
 int /*<<< orphan*/  BD70528_GPIO_OUT_LO ; 
 int /*<<< orphan*/  BD70528_GPIO_OUT_MASK ; 
 int /*<<< orphan*/  GPIO_OUT_REG (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct bd70528_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bd70528_gpio_set(struct gpio_chip *chip, unsigned int offset,
			     int value)
{
	int ret;
	struct bd70528_gpio *bdgpio = gpiochip_get_data(chip);
	u8 val = (value) ? BD70528_GPIO_OUT_HI : BD70528_GPIO_OUT_LO;

	ret = regmap_update_bits(bdgpio->chip.regmap, GPIO_OUT_REG(offset),
				 BD70528_GPIO_OUT_MASK, val);
	if (ret)
		dev_err(bdgpio->chip.dev, "Could not set gpio to %d\n", value);
}