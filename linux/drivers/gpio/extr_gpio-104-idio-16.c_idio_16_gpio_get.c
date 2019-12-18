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
struct idio_16_gpio {scalar_t__ base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 int EINVAL ; 
 struct idio_16_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned int const inb (scalar_t__) ; 

__attribute__((used)) static int idio_16_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct idio_16_gpio *const idio16gpio = gpiochip_get_data(chip);
	const unsigned mask = BIT(offset-16);

	if (offset < 16)
		return -EINVAL;

	if (offset < 24)
		return !!(inb(idio16gpio->base + 1) & mask);

	return !!(inb(idio16gpio->base + 5) & (mask>>8));
}