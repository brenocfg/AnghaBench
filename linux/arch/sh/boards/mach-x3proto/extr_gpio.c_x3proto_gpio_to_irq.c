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
struct gpio_chip {unsigned int ngpio; } ;

/* Variables and functions */
 int ENXIO ; 
 int irq_create_mapping (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  x3proto_irq_domain ; 

__attribute__((used)) static int x3proto_gpio_to_irq(struct gpio_chip *chip, unsigned gpio)
{
	int virq;

	if (gpio < chip->ngpio)
		virq = irq_create_mapping(x3proto_irq_domain, gpio);
	else
		virq = -ENXIO;

	return virq;
}