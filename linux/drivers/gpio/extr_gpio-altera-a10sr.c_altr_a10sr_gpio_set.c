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
 int /*<<< orphan*/  ALTR_A10SR_LED_REG ; 
 scalar_t__ ALTR_A10SR_LED_VALID_SHIFT ; 
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 struct altr_a10sr_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void altr_a10sr_gpio_set(struct gpio_chip *chip, unsigned int offset,
				int value)
{
	struct altr_a10sr_gpio *gpio = gpiochip_get_data(chip);

	regmap_update_bits(gpio->regmap, ALTR_A10SR_LED_REG,
			   BIT(ALTR_A10SR_LED_VALID_SHIFT + offset),
			   value ? BIT(ALTR_A10SR_LED_VALID_SHIFT + offset)
			   : 0);
}