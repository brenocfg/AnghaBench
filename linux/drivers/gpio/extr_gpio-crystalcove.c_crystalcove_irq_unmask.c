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
struct irq_data {scalar_t__ hwirq; } ;
struct crystalcove_gpio {int set_irq_mask; int /*<<< orphan*/  update; } ;

/* Variables and functions */
 scalar_t__ CRYSTALCOVE_GPIO_NUM ; 
 int /*<<< orphan*/  UPDATE_IRQ_MASK ; 
 struct crystalcove_gpio* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void crystalcove_irq_unmask(struct irq_data *data)
{
	struct crystalcove_gpio *cg =
		gpiochip_get_data(irq_data_get_irq_chip_data(data));

	if (data->hwirq < CRYSTALCOVE_GPIO_NUM) {
		cg->set_irq_mask = false;
		cg->update |= UPDATE_IRQ_MASK;
	}
}