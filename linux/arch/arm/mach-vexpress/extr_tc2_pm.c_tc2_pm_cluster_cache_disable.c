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
 scalar_t__ ARM_CPU_PART_CORTEX_A15 ; 
 int /*<<< orphan*/  all ; 
 int /*<<< orphan*/  cci_disable_port_by_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_cpuid_mpidr () ; 
 scalar_t__ read_cpuid_part () ; 
 int /*<<< orphan*/  v7_exit_coherency_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tc2_pm_cluster_cache_disable(void)
{
	if (read_cpuid_part() == ARM_CPU_PART_CORTEX_A15) {
		/*
		 * On the Cortex-A15 we need to disable
		 * L2 prefetching before flushing the cache.
		 */
		asm volatile(
		"mcr	p15, 1, %0, c15, c0, 3 \n\t"
		"isb	\n\t"
		"dsb	"
		: : "r" (0x400) );
	}

	v7_exit_coherency_flush(all);
	cci_disable_port_by_cpu(read_cpuid_mpidr());
}