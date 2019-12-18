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
typedef  int /*<<< orphan*/  u64 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_andnot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dump_stack () ; 
 struct pt_regs* get_irq_regs () ; 
 int /*<<< orphan*/  pr_emerg (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_irqtrace_events (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wd_cpus_enabled ; 
 int /*<<< orphan*/  wd_smp_cpus_pending ; 
 int /*<<< orphan*/  wd_smp_cpus_stuck ; 
 int /*<<< orphan*/  wd_smp_last_reset_tb ; 
 int /*<<< orphan*/  wd_smp_lock (unsigned long*) ; 
 int /*<<< orphan*/  wd_smp_unlock (unsigned long*) ; 

__attribute__((used)) static void wd_smp_clear_cpu_pending(int cpu, u64 tb)
{
	if (!cpumask_test_cpu(cpu, &wd_smp_cpus_pending)) {
		if (unlikely(cpumask_test_cpu(cpu, &wd_smp_cpus_stuck))) {
			struct pt_regs *regs = get_irq_regs();
			unsigned long flags;

			wd_smp_lock(&flags);

			pr_emerg("CPU %d became unstuck TB:%lld\n",
				 cpu, tb);
			print_irqtrace_events(current);
			if (regs)
				show_regs(regs);
			else
				dump_stack();

			cpumask_clear_cpu(cpu, &wd_smp_cpus_stuck);
			wd_smp_unlock(&flags);
		}
		return;
	}
	cpumask_clear_cpu(cpu, &wd_smp_cpus_pending);
	if (cpumask_empty(&wd_smp_cpus_pending)) {
		unsigned long flags;

		wd_smp_lock(&flags);
		if (cpumask_empty(&wd_smp_cpus_pending)) {
			wd_smp_last_reset_tb = tb;
			cpumask_andnot(&wd_smp_cpus_pending,
					&wd_cpus_enabled,
					&wd_smp_cpus_stuck);
		}
		wd_smp_unlock(&flags);
	}
}