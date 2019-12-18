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
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMMA2RH_GPIO_INT_ST ; 
 unsigned int EMMA2RH_GPIO_IRQ_BASE ; 
 int /*<<< orphan*/  emma2rh_out32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void emma2rh_gpio_irq_ack(struct irq_data *d)
{
	unsigned int irq = d->irq - EMMA2RH_GPIO_IRQ_BASE;

	emma2rh_out32(EMMA2RH_GPIO_INT_ST, ~(1 << irq));
}