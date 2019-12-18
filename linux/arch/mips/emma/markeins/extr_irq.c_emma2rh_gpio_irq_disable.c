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
typedef  int u32 ;
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMMA2RH_GPIO_INT_MASK ; 
 unsigned int EMMA2RH_GPIO_IRQ_BASE ; 
 int emma2rh_in32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emma2rh_out32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void emma2rh_gpio_irq_disable(struct irq_data *d)
{
	unsigned int irq = d->irq - EMMA2RH_GPIO_IRQ_BASE;
	u32 reg;

	reg = emma2rh_in32(EMMA2RH_GPIO_INT_MASK);
	reg &= ~(1 << irq);
	emma2rh_out32(EMMA2RH_GPIO_INT_MASK, reg);
}