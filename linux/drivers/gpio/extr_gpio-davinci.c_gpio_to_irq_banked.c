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
struct davinci_gpio_controller {scalar_t__ irq_domain; } ;

/* Variables and functions */
 int ENXIO ; 
 struct davinci_gpio_controller* gpiochip_get_data (struct gpio_chip*) ; 
 int irq_create_mapping (scalar_t__,unsigned int) ; 

__attribute__((used)) static int gpio_to_irq_banked(struct gpio_chip *chip, unsigned offset)
{
	struct davinci_gpio_controller *d = gpiochip_get_data(chip);

	if (d->irq_domain)
		return irq_create_mapping(d->irq_domain, offset);
	else
		return -ENXIO;
}