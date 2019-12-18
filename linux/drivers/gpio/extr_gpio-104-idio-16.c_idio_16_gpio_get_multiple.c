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
 unsigned long GENMASK (int,int) ; 
 struct idio_16_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 scalar_t__ inb (scalar_t__) ; 

__attribute__((used)) static int idio_16_gpio_get_multiple(struct gpio_chip *chip,
	unsigned long *mask, unsigned long *bits)
{
	struct idio_16_gpio *const idio16gpio = gpiochip_get_data(chip);

	*bits = 0;
	if (*mask & GENMASK(23, 16))
		*bits |= (unsigned long)inb(idio16gpio->base + 1) << 16;
	if (*mask & GENMASK(31, 24))
		*bits |= (unsigned long)inb(idio16gpio->base + 5) << 24;

	return 0;
}