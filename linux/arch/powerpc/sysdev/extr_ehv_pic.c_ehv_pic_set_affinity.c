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
struct irq_data {int /*<<< orphan*/  irq; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int IRQ_SET_MASK_OK ; 
 int /*<<< orphan*/  ehv_pic_lock ; 
 int /*<<< orphan*/  ev_int_get_config (unsigned int,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  ev_int_set_config (unsigned int,unsigned int,unsigned int,int) ; 
 int irq_choose_cpu (struct cpumask const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int virq_to_hw (int /*<<< orphan*/ ) ; 

int ehv_pic_set_affinity(struct irq_data *d, const struct cpumask *dest,
			 bool force)
{
	unsigned int src = virq_to_hw(d->irq);
	unsigned int config, prio, cpu_dest;
	int cpuid = irq_choose_cpu(dest);
	unsigned long flags;

	spin_lock_irqsave(&ehv_pic_lock, flags);
	ev_int_get_config(src, &config, &prio, &cpu_dest);
	ev_int_set_config(src, config, prio, cpuid);
	spin_unlock_irqrestore(&ehv_pic_lock, flags);

	return IRQ_SET_MASK_OK;
}