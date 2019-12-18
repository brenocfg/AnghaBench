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
struct irq_data {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_GFER ; 
 int /*<<< orphan*/  GPIO_GRER ; 
 unsigned int GPIO_IRQ_falling_edge ; 
 unsigned int GPIO_IRQ_mask ; 
 unsigned int GPIO_IRQ_rising_edge ; 
 unsigned int GPIO_MASK (int) ; 
 int IRQ_GPIOHIGH ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_PROBE ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int puv3_gpio_type(struct irq_data *d, unsigned int type)
{
	unsigned int mask;

	if (d->irq < IRQ_GPIOHIGH)
		mask = 1 << d->irq;
	else
		mask = GPIO_MASK(d->irq);

	if (type == IRQ_TYPE_PROBE) {
		if ((GPIO_IRQ_rising_edge | GPIO_IRQ_falling_edge) & mask)
			return 0;
		type = IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING;
	}

	if (type & IRQ_TYPE_EDGE_RISING)
		GPIO_IRQ_rising_edge |= mask;
	else
		GPIO_IRQ_rising_edge &= ~mask;
	if (type & IRQ_TYPE_EDGE_FALLING)
		GPIO_IRQ_falling_edge |= mask;
	else
		GPIO_IRQ_falling_edge &= ~mask;

	writel(GPIO_IRQ_rising_edge & GPIO_IRQ_mask, GPIO_GRER);
	writel(GPIO_IRQ_falling_edge & GPIO_IRQ_mask, GPIO_GFER);

	return 0;
}