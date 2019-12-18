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
struct irq_domain {struct ehv_pic* host_data; } ;
struct irq_chip {int dummy; } ;
struct ehv_pic {struct irq_chip hc_irq; } ;
typedef  size_t irq_hw_number_t ;

/* Variables and functions */
 int IRQ_TYPE_MPIC_DIRECT ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 struct irq_chip ehv_pic_direct_eoi_irq_chip ; 
 int /*<<< orphan*/  handle_fasteoi_irq ; 
 int* hwirq_intspec ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,struct irq_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct irq_chip*) ; 
 int /*<<< orphan*/  irq_set_irq_type (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ mpic_percpu_base_vaddr ; 

__attribute__((used)) static int ehv_pic_host_map(struct irq_domain *h, unsigned int virq,
			 irq_hw_number_t hw)
{
	struct ehv_pic *ehv_pic = h->host_data;
	struct irq_chip *chip;

	/* Default chip */
	chip = &ehv_pic->hc_irq;

	if (mpic_percpu_base_vaddr)
		if (hwirq_intspec[hw] & IRQ_TYPE_MPIC_DIRECT)
			chip = &ehv_pic_direct_eoi_irq_chip;

	irq_set_chip_data(virq, chip);
	/*
	 * using handle_fasteoi_irq as our irq handler, this will
	 * only call the eoi callback and suitable for the MPIC
	 * controller which set ISR/IPR automatically and clear the
	 * highest priority active interrupt in ISR/IPR when we do
	 * a specific eoi
	 */
	irq_set_chip_and_handler(virq, chip, handle_fasteoi_irq);

	/* Set default irq type */
	irq_set_irq_type(virq, IRQ_TYPE_NONE);

	return 0;
}