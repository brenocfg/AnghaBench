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
struct irq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ic_siexr; } ;

/* Variables and functions */
 unsigned int CPM2_IRQ_EXT1 ; 
 unsigned int CPM2_IRQ_EXT7 ; 
 unsigned int CPM2_IRQ_PORTC0 ; 
 unsigned int CPM2_IRQ_PORTC15 ; 
 int EINVAL ; 
 int IRQ_SET_MASK_OK_NOCOPY ; 
 unsigned int IRQ_TYPE_EDGE_BOTH ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 unsigned int IRQ_TYPE_NONE ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 TYPE_1__* cpm2_intctl ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 unsigned int in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqd_set_trigger_type (struct irq_data*,unsigned int) ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 

__attribute__((used)) static int cpm2_set_irq_type(struct irq_data *d, unsigned int flow_type)
{
	unsigned int src = irqd_to_hwirq(d);
	unsigned int vold, vnew, edibit;

	/* Port C interrupts are either IRQ_TYPE_EDGE_FALLING or
	 * IRQ_TYPE_EDGE_BOTH (default).  All others are IRQ_TYPE_EDGE_FALLING
	 * or IRQ_TYPE_LEVEL_LOW (default)
	 */
	if (src >= CPM2_IRQ_PORTC15 && src <= CPM2_IRQ_PORTC0) {
		if (flow_type == IRQ_TYPE_NONE)
			flow_type = IRQ_TYPE_EDGE_BOTH;

		if (flow_type != IRQ_TYPE_EDGE_BOTH &&
		    flow_type != IRQ_TYPE_EDGE_FALLING)
			goto err_sense;
	} else {
		if (flow_type == IRQ_TYPE_NONE)
			flow_type = IRQ_TYPE_LEVEL_LOW;

		if (flow_type & (IRQ_TYPE_EDGE_RISING | IRQ_TYPE_LEVEL_HIGH))
			goto err_sense;
	}

	irqd_set_trigger_type(d, flow_type);
	if (flow_type & IRQ_TYPE_LEVEL_LOW)
		irq_set_handler_locked(d, handle_level_irq);
	else
		irq_set_handler_locked(d, handle_edge_irq);

	/* internal IRQ senses are LEVEL_LOW
	 * EXT IRQ and Port C IRQ senses are programmable
	 */
	if (src >= CPM2_IRQ_EXT1 && src <= CPM2_IRQ_EXT7)
			edibit = (14 - (src - CPM2_IRQ_EXT1));
	else
		if (src >= CPM2_IRQ_PORTC15 && src <= CPM2_IRQ_PORTC0)
			edibit = (31 - (CPM2_IRQ_PORTC0 - src));
		else
			return (flow_type & IRQ_TYPE_LEVEL_LOW) ?
				IRQ_SET_MASK_OK_NOCOPY : -EINVAL;

	vold = in_be32(&cpm2_intctl->ic_siexr);

	if ((flow_type & IRQ_TYPE_SENSE_MASK) == IRQ_TYPE_EDGE_FALLING)
		vnew = vold | (1 << edibit);
	else
		vnew = vold & ~(1 << edibit);

	if (vold != vnew)
		out_be32(&cpm2_intctl->ic_siexr, vnew);
	return IRQ_SET_MASK_OK_NOCOPY;

err_sense:
	pr_err("CPM2 PIC: sense type 0x%x not supported\n", flow_type);
	return -EINVAL;
}