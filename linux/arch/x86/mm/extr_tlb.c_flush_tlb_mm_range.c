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
typedef  int /*<<< orphan*/  u64 ;
struct mm_struct {int dummy; } ;
struct flush_tlb_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  loaded_mm; } ;

/* Variables and functions */
 unsigned long TLB_FLUSH_ALL ; 
 int /*<<< orphan*/  TLB_LOCAL_MM_SHOOTDOWN ; 
 TYPE_1__ cpu_tlbstate ; 
 scalar_t__ cpumask_any_but (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flush_tlb_func_local (struct flush_tlb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_tlb_others (int /*<<< orphan*/ ,struct flush_tlb_info*) ; 
 int get_cpu () ; 
 struct flush_tlb_info* get_flush_tlb_info (struct mm_struct*,unsigned long,unsigned long,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_mm_tlb_gen (struct mm_struct*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  lockdep_assert_irqs_enabled () ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 scalar_t__ nr_cpu_ids ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  put_flush_tlb_info () ; 
 struct mm_struct* this_cpu_read (int /*<<< orphan*/ ) ; 
 unsigned long tlb_single_page_flush_ceiling ; 

void flush_tlb_mm_range(struct mm_struct *mm, unsigned long start,
				unsigned long end, unsigned int stride_shift,
				bool freed_tables)
{
	struct flush_tlb_info *info;
	u64 new_tlb_gen;
	int cpu;

	cpu = get_cpu();

	/* Should we flush just the requested range? */
	if ((end == TLB_FLUSH_ALL) ||
	    ((end - start) >> stride_shift) > tlb_single_page_flush_ceiling) {
		start = 0;
		end = TLB_FLUSH_ALL;
	}

	/* This is also a barrier that synchronizes with switch_mm(). */
	new_tlb_gen = inc_mm_tlb_gen(mm);

	info = get_flush_tlb_info(mm, start, end, stride_shift, freed_tables,
				  new_tlb_gen);

	if (mm == this_cpu_read(cpu_tlbstate.loaded_mm)) {
		lockdep_assert_irqs_enabled();
		local_irq_disable();
		flush_tlb_func_local(info, TLB_LOCAL_MM_SHOOTDOWN);
		local_irq_enable();
	}

	if (cpumask_any_but(mm_cpumask(mm), cpu) < nr_cpu_ids)
		flush_tlb_others(mm_cpumask(mm), info);

	put_flush_tlb_info();
	put_cpu();
}