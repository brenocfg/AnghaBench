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
struct irq_data {int dummy; } ;
struct gpio_chip {int dummy; } ;
struct dln2_gpio {int /*<<< orphan*/ * irq_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLN2_GPIO_EVENT_CHANGE ; 
 int /*<<< orphan*/  DLN2_GPIO_EVENT_CHANGE_FALLING ; 
 int /*<<< orphan*/  DLN2_GPIO_EVENT_CHANGE_RISING ; 
 int /*<<< orphan*/  DLN2_GPIO_EVENT_LVL_HIGH ; 
 int /*<<< orphan*/  DLN2_GPIO_EVENT_LVL_LOW ; 
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 struct dln2_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int irqd_to_hwirq (struct irq_data*) ; 

__attribute__((used)) static int dln2_irq_set_type(struct irq_data *irqd, unsigned type)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	struct dln2_gpio *dln2 = gpiochip_get_data(gc);
	int pin = irqd_to_hwirq(irqd);

	switch (type) {
	case IRQ_TYPE_LEVEL_HIGH:
		dln2->irq_type[pin] = DLN2_GPIO_EVENT_LVL_HIGH;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		dln2->irq_type[pin] = DLN2_GPIO_EVENT_LVL_LOW;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		dln2->irq_type[pin] = DLN2_GPIO_EVENT_CHANGE;
		break;
	case IRQ_TYPE_EDGE_RISING:
		dln2->irq_type[pin] = DLN2_GPIO_EVENT_CHANGE_RISING;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		dln2->irq_type[pin] = DLN2_GPIO_EVENT_CHANGE_FALLING;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}