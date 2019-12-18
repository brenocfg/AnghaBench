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

/* Variables and functions */
 int /*<<< orphan*/  IRQ_SUBCLASS_MEASUREMENT_ALERT ; 
 int PMC_RELEASE ; 
 int /*<<< orphan*/  cpum_cf_setup_cpu ; 
 int /*<<< orphan*/ * cpumcf_owner ; 
 int /*<<< orphan*/  cpumcf_owner_lock ; 
 int /*<<< orphan*/  irq_subclass_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void __kernel_cpumcf_end(void)
{
	int flags = PMC_RELEASE;

	on_each_cpu(cpum_cf_setup_cpu, &flags, 1);
	irq_subclass_unregister(IRQ_SUBCLASS_MEASUREMENT_ALERT);

	spin_lock(&cpumcf_owner_lock);
	cpumcf_owner = NULL;
	spin_unlock(&cpumcf_owner_lock);
}