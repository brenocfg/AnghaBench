#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct irq_data {int irq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq_unmask ) (struct irq_data*) ;} ;

/* Variables and functions */
 int AMS_DELTA_GPIO_PIN_HOOK_SWITCH ; 
 int AMS_DELTA_GPIO_PIN_KEYBRD_CLK ; 
 int FIQ_CNT_INT_00 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int* fiq_buffer ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 TYPE_1__* irq_chip ; 
 int* irq_counter ; 
 struct irq_data** irq_data ; 
 int /*<<< orphan*/  stub1 (struct irq_data*) ; 

__attribute__((used)) static irqreturn_t deferred_fiq(int irq, void *dev_id)
{
	struct irq_data *d;
	int gpio, irq_num, fiq_count;

	/*
	 * For each handled GPIO interrupt, keep calling its interrupt handler
	 * until the IRQ counter catches the FIQ incremented interrupt counter.
	 */
	for (gpio = AMS_DELTA_GPIO_PIN_KEYBRD_CLK;
			gpio <= AMS_DELTA_GPIO_PIN_HOOK_SWITCH; gpio++) {
		d = irq_data[gpio];
		irq_num = d->irq;
		fiq_count = fiq_buffer[FIQ_CNT_INT_00 + gpio];

		if (irq_counter[gpio] < fiq_count &&
				gpio != AMS_DELTA_GPIO_PIN_KEYBRD_CLK) {
			/*
			 * handle_simple_irq() that OMAP GPIO edge
			 * interrupts default to since commit 80ac93c27441
			 * requires interrupt already acked and unmasked.
			 */
			if (!WARN_ON_ONCE(!irq_chip->irq_unmask))
				irq_chip->irq_unmask(d);
		}
		for (; irq_counter[gpio] < fiq_count; irq_counter[gpio]++)
			generic_handle_irq(irq_num);
	}
	return IRQ_HANDLED;
}