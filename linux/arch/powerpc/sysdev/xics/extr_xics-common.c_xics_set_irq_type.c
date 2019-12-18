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

/* Variables and functions */
 int EINVAL ; 
 int IRQ_SET_MASK_OK_NOCOPY ; 
 unsigned int IRQ_TYPE_DEFAULT ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 unsigned int IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  irqd_set_trigger_type (struct irq_data*,unsigned int) ; 

int xics_set_irq_type(struct irq_data *d, unsigned int flow_type)
{
	/*
	 * We only support these. This has really no effect other than setting
	 * the corresponding descriptor bits mind you but those will in turn
	 * affect the resend function when re-enabling an edge interrupt.
	 *
	 * Set set the default to edge as explained in map().
	 */
	if (flow_type == IRQ_TYPE_DEFAULT || flow_type == IRQ_TYPE_NONE)
		flow_type = IRQ_TYPE_EDGE_RISING;

	if (flow_type != IRQ_TYPE_EDGE_RISING &&
	    flow_type != IRQ_TYPE_LEVEL_LOW)
		return -EINVAL;

	irqd_set_trigger_type(d, flow_type);

	return IRQ_SET_MASK_OK_NOCOPY;
}