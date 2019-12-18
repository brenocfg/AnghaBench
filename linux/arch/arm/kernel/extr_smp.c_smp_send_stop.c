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
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPI_CPU_STOP ; 
 unsigned long USEC_PER_SEC ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int /*<<< orphan*/ ,struct cpumask*) ; 
 int /*<<< orphan*/  cpumask_copy (struct cpumask*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_empty (struct cpumask*) ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  smp_cross_call (struct cpumask*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  udelay (int) ; 

void smp_send_stop(void)
{
	unsigned long timeout;
	struct cpumask mask;

	cpumask_copy(&mask, cpu_online_mask);
	cpumask_clear_cpu(smp_processor_id(), &mask);
	if (!cpumask_empty(&mask))
		smp_cross_call(&mask, IPI_CPU_STOP);

	/* Wait up to one second for other CPUs to stop */
	timeout = USEC_PER_SEC;
	while (num_online_cpus() > 1 && timeout--)
		udelay(1);

	if (num_online_cpus() > 1)
		pr_warn("SMP: failed to stop secondary CPUs\n");
}