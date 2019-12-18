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
struct irq_data {unsigned long hwirq; } ;

/* Variables and functions */
 int BIT (unsigned long) ; 
 unsigned long INT_NUM_IM_OFFSET ; 
 int /*<<< orphan*/  LTQ_ICU_IER ; 
 unsigned long MIPS_CPU_IRQ_CASCADE ; 
 int cpumask_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_get_effective_affinity_mask (struct irq_data*) ; 
 int /*<<< orphan*/  ltq_icu_lock ; 
 int ltq_icu_r32 (int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_icu_w32 (int,unsigned long,int,int /*<<< orphan*/ ) ; 
 int nr_cpu_ids ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 

void ltq_enable_irq(struct irq_data *d)
{
	unsigned long offset = d->hwirq - MIPS_CPU_IRQ_CASCADE;
	unsigned long im = offset / INT_NUM_IM_OFFSET;
	unsigned long flags;
	int vpe;

	offset %= INT_NUM_IM_OFFSET;

	vpe = cpumask_first(irq_data_get_effective_affinity_mask(d));

	/* This shouldn't be even possible, maybe during CPU hotplug spam */
	if (unlikely(vpe >= nr_cpu_ids))
		vpe = smp_processor_id();

	raw_spin_lock_irqsave(&ltq_icu_lock, flags);

	ltq_icu_w32(vpe, im, ltq_icu_r32(vpe, im, LTQ_ICU_IER) | BIT(offset),
		    LTQ_ICU_IER);

	raw_spin_unlock_irqrestore(&ltq_icu_lock, flags);
}