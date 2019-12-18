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
struct irq_data {int hwirq; } ;
struct crystalcove_gpio {int update; int /*<<< orphan*/  buslock; } ;

/* Variables and functions */
 int UPDATE_IRQ_MASK ; 
 int UPDATE_IRQ_TYPE ; 
 int /*<<< orphan*/  crystalcove_update_irq_ctrl (struct crystalcove_gpio*,int) ; 
 int /*<<< orphan*/  crystalcove_update_irq_mask (struct crystalcove_gpio*,int) ; 
 struct crystalcove_gpio* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crystalcove_bus_sync_unlock(struct irq_data *data)
{
	struct crystalcove_gpio *cg =
		gpiochip_get_data(irq_data_get_irq_chip_data(data));
	int gpio = data->hwirq;

	if (cg->update & UPDATE_IRQ_TYPE)
		crystalcove_update_irq_ctrl(cg, gpio);
	if (cg->update & UPDATE_IRQ_MASK)
		crystalcove_update_irq_mask(cg, gpio);
	cg->update = 0;

	mutex_unlock(&cg->buslock);
}