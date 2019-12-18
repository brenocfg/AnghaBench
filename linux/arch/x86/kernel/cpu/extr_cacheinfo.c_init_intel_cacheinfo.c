#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cpuinfo_x86 {unsigned int cpu_index; int cpuid_level; int apicid; int x86; unsigned int phys_proc_id; unsigned int x86_cache_size; } ;
struct TYPE_4__ {int level; int /*<<< orphan*/  num_threads_sharing; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {TYPE_1__ split; } ;
struct _cpuid4_info_regs {int size; TYPE_2__ eax; } ;
struct TYPE_6__ {unsigned char descriptor; int cache_type; unsigned int size; } ;

/* Variables and functions */
 unsigned int BAD_APICID ; 
 int /*<<< orphan*/  CTYPE_DATA ; 
 int /*<<< orphan*/  CTYPE_INST ; 
#define  LVL_1_DATA 132 
#define  LVL_1_INST 131 
#define  LVL_2 130 
#define  LVL_3 129 
#define  LVL_TRACE 128 
 TYPE_3__* cache_table ; 
 int /*<<< orphan*/  cpu_detect_cache_sizes (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  cpu_llc_id ; 
 int /*<<< orphan*/  cpuid (int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int cpuid4_cache_lookup_regs (unsigned int,struct _cpuid4_info_regs*) ; 
 int cpuid_eax (int) ; 
 unsigned int find_num_cache_leaves (struct cpuinfo_x86*) ; 
 unsigned int get_count_order (unsigned int) ; 
 unsigned int num_cache_leaves ; 
 unsigned int per_cpu (int /*<<< orphan*/ ,unsigned int) ; 

void init_intel_cacheinfo(struct cpuinfo_x86 *c)
{
	/* Cache sizes */
	unsigned int trace = 0, l1i = 0, l1d = 0, l2 = 0, l3 = 0;
	unsigned int new_l1d = 0, new_l1i = 0; /* Cache sizes from cpuid(4) */
	unsigned int new_l2 = 0, new_l3 = 0, i; /* Cache sizes from cpuid(4) */
	unsigned int l2_id = 0, l3_id = 0, num_threads_sharing, index_msb;
#ifdef CONFIG_SMP
	unsigned int cpu = c->cpu_index;
#endif

	if (c->cpuid_level > 3) {
		static int is_initialized;

		if (is_initialized == 0) {
			/* Init num_cache_leaves from boot CPU */
			num_cache_leaves = find_num_cache_leaves(c);
			is_initialized++;
		}

		/*
		 * Whenever possible use cpuid(4), deterministic cache
		 * parameters cpuid leaf to find the cache details
		 */
		for (i = 0; i < num_cache_leaves; i++) {
			struct _cpuid4_info_regs this_leaf = {};
			int retval;

			retval = cpuid4_cache_lookup_regs(i, &this_leaf);
			if (retval < 0)
				continue;

			switch (this_leaf.eax.split.level) {
			case 1:
				if (this_leaf.eax.split.type == CTYPE_DATA)
					new_l1d = this_leaf.size/1024;
				else if (this_leaf.eax.split.type == CTYPE_INST)
					new_l1i = this_leaf.size/1024;
				break;
			case 2:
				new_l2 = this_leaf.size/1024;
				num_threads_sharing = 1 + this_leaf.eax.split.num_threads_sharing;
				index_msb = get_count_order(num_threads_sharing);
				l2_id = c->apicid & ~((1 << index_msb) - 1);
				break;
			case 3:
				new_l3 = this_leaf.size/1024;
				num_threads_sharing = 1 + this_leaf.eax.split.num_threads_sharing;
				index_msb = get_count_order(num_threads_sharing);
				l3_id = c->apicid & ~((1 << index_msb) - 1);
				break;
			default:
				break;
			}
		}
	}
	/*
	 * Don't use cpuid2 if cpuid4 is supported. For P4, we use cpuid2 for
	 * trace cache
	 */
	if ((num_cache_leaves == 0 || c->x86 == 15) && c->cpuid_level > 1) {
		/* supports eax=2  call */
		int j, n;
		unsigned int regs[4];
		unsigned char *dp = (unsigned char *)regs;
		int only_trace = 0;

		if (num_cache_leaves != 0 && c->x86 == 15)
			only_trace = 1;

		/* Number of times to iterate */
		n = cpuid_eax(2) & 0xFF;

		for (i = 0 ; i < n ; i++) {
			cpuid(2, &regs[0], &regs[1], &regs[2], &regs[3]);

			/* If bit 31 is set, this is an unknown format */
			for (j = 0 ; j < 3 ; j++)
				if (regs[j] & (1 << 31))
					regs[j] = 0;

			/* Byte 0 is level count, not a descriptor */
			for (j = 1 ; j < 16 ; j++) {
				unsigned char des = dp[j];
				unsigned char k = 0;

				/* look up this descriptor in the table */
				while (cache_table[k].descriptor != 0) {
					if (cache_table[k].descriptor == des) {
						if (only_trace && cache_table[k].cache_type != LVL_TRACE)
							break;
						switch (cache_table[k].cache_type) {
						case LVL_1_INST:
							l1i += cache_table[k].size;
							break;
						case LVL_1_DATA:
							l1d += cache_table[k].size;
							break;
						case LVL_2:
							l2 += cache_table[k].size;
							break;
						case LVL_3:
							l3 += cache_table[k].size;
							break;
						case LVL_TRACE:
							trace += cache_table[k].size;
							break;
						}

						break;
					}

					k++;
				}
			}
		}
	}

	if (new_l1d)
		l1d = new_l1d;

	if (new_l1i)
		l1i = new_l1i;

	if (new_l2) {
		l2 = new_l2;
#ifdef CONFIG_SMP
		per_cpu(cpu_llc_id, cpu) = l2_id;
#endif
	}

	if (new_l3) {
		l3 = new_l3;
#ifdef CONFIG_SMP
		per_cpu(cpu_llc_id, cpu) = l3_id;
#endif
	}

#ifdef CONFIG_SMP
	/*
	 * If cpu_llc_id is not yet set, this means cpuid_level < 4 which in
	 * turns means that the only possibility is SMT (as indicated in
	 * cpuid1). Since cpuid2 doesn't specify shared caches, and we know
	 * that SMT shares all caches, we can unconditionally set cpu_llc_id to
	 * c->phys_proc_id.
	 */
	if (per_cpu(cpu_llc_id, cpu) == BAD_APICID)
		per_cpu(cpu_llc_id, cpu) = c->phys_proc_id;
#endif

	c->x86_cache_size = l3 ? l3 : (l2 ? l2 : (l1i+l1d));

	if (!l2)
		cpu_detect_cache_sizes(c);
}