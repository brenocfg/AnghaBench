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
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct cpumask {int dummy; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IDU_M_DISTRI_DEST ; 
 unsigned int IDU_M_DISTRI_RR ; 
 int IRQ_SET_MASK_OK ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_and (int /*<<< orphan*/ *,struct cpumask const*,int /*<<< orphan*/ ) ; 
 unsigned int* cpumask_bits (int /*<<< orphan*/ *) ; 
 scalar_t__ ffs (unsigned int) ; 
 scalar_t__ fls (unsigned int) ; 
 int /*<<< orphan*/  idu_set_dest (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  idu_set_mode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  mcip_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
idu_irq_set_affinity(struct irq_data *data, const struct cpumask *cpumask,
		     bool force)
{
	unsigned long flags;
	cpumask_t online;
	unsigned int destination_bits;
	unsigned int distribution_mode;

	/* errout if no online cpu per @cpumask */
	if (!cpumask_and(&online, cpumask, cpu_online_mask))
		return -EINVAL;

	raw_spin_lock_irqsave(&mcip_lock, flags);

	destination_bits = cpumask_bits(&online)[0];
	idu_set_dest(data->hwirq, destination_bits);

	if (ffs(destination_bits) == fls(destination_bits))
		distribution_mode = IDU_M_DISTRI_DEST;
	else
		distribution_mode = IDU_M_DISTRI_RR;

	idu_set_mode(data->hwirq, false, 0, true, distribution_mode);

	raw_spin_unlock_irqrestore(&mcip_lock, flags);

	return IRQ_SET_MASK_OK;
}