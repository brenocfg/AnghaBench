#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpuinfo_x86 {unsigned int initial_apicid; unsigned int cpu_core_id; unsigned int cpu_die_id; unsigned int phys_proc_id; unsigned int apicid; unsigned int x86_max_cores; } ;
struct TYPE_2__ {unsigned int (* phys_pkg_id ) (unsigned int,unsigned int) ;} ;

/* Variables and functions */
 unsigned int BITS_SHIFT_NEXT_LEVEL (unsigned int) ; 
 scalar_t__ CORE_TYPE ; 
 scalar_t__ DIE_TYPE ; 
 scalar_t__ INVALID_TYPE ; 
 scalar_t__ LEAFB_SUBTYPE (unsigned int) ; 
 unsigned int LEVEL_MAX_SIBLINGS (unsigned int) ; 
 unsigned int SMT_LEVEL ; 
 unsigned int __max_die_per_package ; 
 TYPE_1__* apic ; 
 int /*<<< orphan*/  cpuid_count (int,unsigned int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int detect_extended_topology_leaf (struct cpuinfo_x86*) ; 
 unsigned int smp_num_siblings ; 
 unsigned int stub1 (unsigned int,unsigned int) ; 
 unsigned int stub2 (unsigned int,unsigned int) ; 
 unsigned int stub3 (unsigned int,unsigned int) ; 
 unsigned int stub4 (unsigned int,unsigned int) ; 

int detect_extended_topology(struct cpuinfo_x86 *c)
{
#ifdef CONFIG_SMP
	unsigned int eax, ebx, ecx, edx, sub_index;
	unsigned int ht_mask_width, core_plus_mask_width, die_plus_mask_width;
	unsigned int core_select_mask, core_level_siblings;
	unsigned int die_select_mask, die_level_siblings;
	int leaf;

	leaf = detect_extended_topology_leaf(c);
	if (leaf < 0)
		return -1;

	/*
	 * Populate HT related information from sub-leaf level 0.
	 */
	cpuid_count(leaf, SMT_LEVEL, &eax, &ebx, &ecx, &edx);
	c->initial_apicid = edx;
	core_level_siblings = smp_num_siblings = LEVEL_MAX_SIBLINGS(ebx);
	core_plus_mask_width = ht_mask_width = BITS_SHIFT_NEXT_LEVEL(eax);
	die_level_siblings = LEVEL_MAX_SIBLINGS(ebx);
	die_plus_mask_width = BITS_SHIFT_NEXT_LEVEL(eax);

	sub_index = 1;
	do {
		cpuid_count(leaf, sub_index, &eax, &ebx, &ecx, &edx);

		/*
		 * Check for the Core type in the implemented sub leaves.
		 */
		if (LEAFB_SUBTYPE(ecx) == CORE_TYPE) {
			core_level_siblings = LEVEL_MAX_SIBLINGS(ebx);
			core_plus_mask_width = BITS_SHIFT_NEXT_LEVEL(eax);
			die_level_siblings = core_level_siblings;
			die_plus_mask_width = BITS_SHIFT_NEXT_LEVEL(eax);
		}
		if (LEAFB_SUBTYPE(ecx) == DIE_TYPE) {
			die_level_siblings = LEVEL_MAX_SIBLINGS(ebx);
			die_plus_mask_width = BITS_SHIFT_NEXT_LEVEL(eax);
		}

		sub_index++;
	} while (LEAFB_SUBTYPE(ecx) != INVALID_TYPE);

	core_select_mask = (~(-1 << core_plus_mask_width)) >> ht_mask_width;
	die_select_mask = (~(-1 << die_plus_mask_width)) >>
				core_plus_mask_width;

	c->cpu_core_id = apic->phys_pkg_id(c->initial_apicid,
				ht_mask_width) & core_select_mask;
	c->cpu_die_id = apic->phys_pkg_id(c->initial_apicid,
				core_plus_mask_width) & die_select_mask;
	c->phys_proc_id = apic->phys_pkg_id(c->initial_apicid,
				die_plus_mask_width);
	/*
	 * Reinit the apicid, now that we have extended initial_apicid.
	 */
	c->apicid = apic->phys_pkg_id(c->initial_apicid, 0);

	c->x86_max_cores = (core_level_siblings / smp_num_siblings);
	__max_die_per_package = (die_level_siblings / core_level_siblings);
#endif
	return 0;
}