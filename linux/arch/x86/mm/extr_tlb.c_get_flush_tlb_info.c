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
struct mm_struct {int dummy; } ;
struct flush_tlb_info {unsigned long start; unsigned long end; unsigned int stride_shift; int freed_tables; int /*<<< orphan*/  new_tlb_gen; struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  flush_tlb_info ; 
 int /*<<< orphan*/  flush_tlb_info_idx ; 
 int this_cpu_inc_return (int /*<<< orphan*/ ) ; 
 struct flush_tlb_info* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct flush_tlb_info *get_flush_tlb_info(struct mm_struct *mm,
			unsigned long start, unsigned long end,
			unsigned int stride_shift, bool freed_tables,
			u64 new_tlb_gen)
{
	struct flush_tlb_info *info = this_cpu_ptr(&flush_tlb_info);

#ifdef CONFIG_DEBUG_VM
	/*
	 * Ensure that the following code is non-reentrant and flush_tlb_info
	 * is not overwritten. This means no TLB flushing is initiated by
	 * interrupt handlers and machine-check exception handlers.
	 */
	BUG_ON(this_cpu_inc_return(flush_tlb_info_idx) != 1);
#endif

	info->start		= start;
	info->end		= end;
	info->mm		= mm;
	info->stride_shift	= stride_shift;
	info->freed_tables	= freed_tables;
	info->new_tlb_gen	= new_tlb_gen;

	return info;
}