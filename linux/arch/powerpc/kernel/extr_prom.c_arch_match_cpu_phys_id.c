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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int* cpu_to_phys_id ; 
 int get_hard_smp_processor_id (int) ; 

bool arch_match_cpu_phys_id(int cpu, u64 phys_id)
{
#ifdef CONFIG_SMP
	/*
	 * Early firmware scanning must use this rather than
	 * get_hard_smp_processor_id because we don't have pacas allocated
	 * until memory topology is discovered.
	 */
	if (cpu_to_phys_id != NULL)
		return (int)phys_id == cpu_to_phys_id[cpu];
#endif

	return (int)phys_id == get_hard_smp_processor_id(cpu);
}