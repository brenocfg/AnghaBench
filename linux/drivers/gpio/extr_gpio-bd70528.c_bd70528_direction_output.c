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
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct bd70528_gpio {TYPE_1__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD70528_GPIO_OUT_ENABLE ; 
 int /*<<< orphan*/  BD70528_GPIO_OUT_EN_MASK ; 
 int /*<<< orphan*/  GPIO_OUT_REG (unsigned int) ; 
 int /*<<< orphan*/  bd70528_gpio_set (struct gpio_chip*,unsigned int,int) ; 
 struct bd70528_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bd70528_direction_output(struct gpio_chip *chip, unsigned int offset,
				    int value)
{
	struct bd70528_gpio *bdgpio = gpiochip_get_data(chip);

	bd70528_gpio_set(chip, offset, value);
	return regmap_update_bits(bdgpio->chip.regmap, GPIO_OUT_REG(offset),
				 BD70528_GPIO_OUT_EN_MASK,
				 BD70528_GPIO_OUT_ENABLE);
}