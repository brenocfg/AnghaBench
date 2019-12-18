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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpus_in_crash ; 
 int /*<<< orphan*/  crash_kexec_prepare_cpus () ; 
 int /*<<< orphan*/  crash_save_cpu (struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crashing_cpu ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void default_machine_crash_shutdown(struct pt_regs *regs)
{
	local_irq_disable();
	crashing_cpu = smp_processor_id();
	crash_save_cpu(regs, crashing_cpu);
	crash_kexec_prepare_cpus();
	cpumask_set_cpu(crashing_cpu, &cpus_in_crash);
}