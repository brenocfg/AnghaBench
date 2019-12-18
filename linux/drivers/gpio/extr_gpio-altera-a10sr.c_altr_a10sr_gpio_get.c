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
struct altr_a10sr_gpio {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ ALTR_A10SR_LED_VALID_SHIFT ; 
 int /*<<< orphan*/  ALTR_A10SR_PBDSW_REG ; 
 int BIT (scalar_t__) ; 
 struct altr_a10sr_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int altr_a10sr_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	struct altr_a10sr_gpio *gpio = gpiochip_get_data(chip);
	int ret, val;

	ret = regmap_read(gpio->regmap, ALTR_A10SR_PBDSW_REG, &val);
	if (ret < 0)
		return ret;

	return !!(val & BIT(offset - ALTR_A10SR_LED_VALID_SHIFT));
}