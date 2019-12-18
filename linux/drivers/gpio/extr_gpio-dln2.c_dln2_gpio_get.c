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
struct dln2_gpio {int dummy; } ;

/* Variables and functions */
 int dln2_gpio_get_direction (struct gpio_chip*,unsigned int) ; 
 int dln2_gpio_pin_get_in_val (struct dln2_gpio*,unsigned int) ; 
 int dln2_gpio_pin_get_out_val (struct dln2_gpio*,unsigned int) ; 
 struct dln2_gpio* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int dln2_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	struct dln2_gpio *dln2 = gpiochip_get_data(chip);
	int dir;

	dir = dln2_gpio_get_direction(chip, offset);
	if (dir < 0)
		return dir;

	if (dir == 1)
		return dln2_gpio_pin_get_in_val(dln2, offset);

	return dln2_gpio_pin_get_out_val(dln2, offset);
}