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
struct mxc_extra_irq {int (* set_irq_fiq ) (int /*<<< orphan*/ ,unsigned int) ;} ;
struct irq_data {int dummy; } ;
struct irq_chip_generic {struct mxc_extra_irq* private; } ;

/* Variables and functions */
 int ENOSYS ; 
 struct irq_chip_generic* irq_get_chip_data (unsigned int) ; 
 struct irq_data* irq_get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int) ; 

int mxc_set_irq_fiq(unsigned int irq, unsigned int type)
{
	struct irq_chip_generic *gc;
	struct mxc_extra_irq *exirq;
	int ret;

	ret = -ENOSYS;

	gc = irq_get_chip_data(irq);
	if (gc && gc->private) {
		exirq = gc->private;
		if (exirq->set_irq_fiq) {
			struct irq_data *d = irq_get_irq_data(irq);
			ret = exirq->set_irq_fiq(irqd_to_hwirq(d), type);
		}
	}

	return ret;
}