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
struct cpu_cacheinfo {unsigned int num_leaves; int cpu_map_populated; struct cacheinfo* info_list; } ;
struct cacheinfo {int dummy; } ;
struct _cpuid4_info_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cache_cpumap_setup (unsigned int,unsigned int,struct _cpuid4_info_regs*) ; 
 int /*<<< orphan*/  ci_leaf_init (int /*<<< orphan*/ ,struct _cpuid4_info_regs*) ; 
 unsigned int cpuid4_cache_lookup_regs (unsigned int,struct _cpuid4_info_regs*) ; 
 int /*<<< orphan*/  get_cache_id (unsigned int,struct _cpuid4_info_regs*) ; 
 struct cpu_cacheinfo* get_cpu_cacheinfo (unsigned int) ; 

__attribute__((used)) static int __populate_cache_leaves(unsigned int cpu)
{
	unsigned int idx, ret;
	struct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	struct cacheinfo *this_leaf = this_cpu_ci->info_list;
	struct _cpuid4_info_regs id4_regs = {};

	for (idx = 0; idx < this_cpu_ci->num_leaves; idx++) {
		ret = cpuid4_cache_lookup_regs(idx, &id4_regs);
		if (ret)
			return ret;
		get_cache_id(cpu, &id4_regs);
		ci_leaf_init(this_leaf++, &id4_regs);
		__cache_cpumap_setup(cpu, idx, &id4_regs);
	}
	this_cpu_ci->cpu_map_populated = true;

	return 0;
}