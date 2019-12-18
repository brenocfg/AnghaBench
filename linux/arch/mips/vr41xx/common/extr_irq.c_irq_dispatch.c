#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct irq_desc {int dummy; } ;
struct irq_data {int dummy; } ;
struct irq_chip {int /*<<< orphan*/  (* irq_unmask ) (struct irq_data*) ;int /*<<< orphan*/  (* irq_ack ) (struct irq_data*) ;int /*<<< orphan*/  (* irq_mask ) (struct irq_data*) ;int /*<<< orphan*/  (* irq_mask_ack ) (struct irq_data*) ;} ;
struct TYPE_3__ {int (* get_irq ) (unsigned int) ;} ;
typedef  TYPE_1__ irq_cascade_t ;

/* Variables and functions */
 unsigned int NR_IRQS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_IRQ (unsigned int) ; 
 TYPE_1__* irq_cascade ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct irq_data* irq_desc_get_irq_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_err_count ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  irqd_irq_disabled (struct irq_data*) ; 
 int /*<<< orphan*/  stub1 (struct irq_data*) ; 
 int /*<<< orphan*/  stub2 (struct irq_data*) ; 
 int /*<<< orphan*/  stub3 (struct irq_data*) ; 
 int stub4 (unsigned int) ; 
 int /*<<< orphan*/  stub5 (struct irq_data*) ; 

__attribute__((used)) static void irq_dispatch(unsigned int irq)
{
	irq_cascade_t *cascade;

	if (irq >= NR_IRQS) {
		atomic_inc(&irq_err_count);
		return;
	}

	cascade = irq_cascade + irq;
	if (cascade->get_irq != NULL) {
		struct irq_desc *desc = irq_to_desc(irq);
		struct irq_data *idata = irq_desc_get_irq_data(desc);
		struct irq_chip *chip = irq_desc_get_chip(desc);
		int ret;

		if (chip->irq_mask_ack)
			chip->irq_mask_ack(idata);
		else {
			chip->irq_mask(idata);
			chip->irq_ack(idata);
		}
		ret = cascade->get_irq(irq);
		irq = ret;
		if (ret < 0)
			atomic_inc(&irq_err_count);
		else
			irq_dispatch(irq);
		if (!irqd_irq_disabled(idata) && chip->irq_unmask)
			chip->irq_unmask(idata);
	} else
		do_IRQ(irq);
}