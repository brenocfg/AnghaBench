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
struct mce {int inject_flags; } ;

/* Variables and functions */
 int MCJ_EXCEPTION ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  injectm ; 
 int /*<<< orphan*/  mce_inject_cpumask ; 
 int /*<<< orphan*/  raise_exception (struct mce*,int /*<<< orphan*/ *) ; 
 int smp_processor_id () ; 
 struct mce* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mce_irq_ipi(void *info)
{
	int cpu = smp_processor_id();
	struct mce *m = this_cpu_ptr(&injectm);

	if (cpumask_test_cpu(cpu, mce_inject_cpumask) &&
			m->inject_flags & MCJ_EXCEPTION) {
		cpumask_clear_cpu(cpu, mce_inject_cpumask);
		raise_exception(m, NULL);
	}
}