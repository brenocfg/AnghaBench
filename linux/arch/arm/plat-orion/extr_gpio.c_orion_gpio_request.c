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
struct orion_gpio_chip {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_INPUT_OK ; 
 int /*<<< orphan*/  GPIO_OUTPUT_OK ; 
 struct orion_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 scalar_t__ orion_gpio_is_valid (struct orion_gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int orion_gpio_request(struct gpio_chip *chip, unsigned pin)
{
	struct orion_gpio_chip *ochip = gpiochip_get_data(chip);

	if (orion_gpio_is_valid(ochip, pin, GPIO_INPUT_OK) ||
	    orion_gpio_is_valid(ochip, pin, GPIO_OUTPUT_OK))
		return 0;

	return -EINVAL;
}