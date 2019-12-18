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
struct mmu_gather {int page_size; unsigned long start; unsigned long end; scalar_t__ need_flush_all; scalar_t__ fullmm; struct mm_struct* mm; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __flush_all_mm (struct mm_struct*,int) ; 
 int /*<<< orphan*/  __radix__flush_tlb_range (struct mm_struct*,unsigned long,unsigned long,int) ; 
 scalar_t__ mm_tlb_flush_nested (struct mm_struct*) ; 
 int /*<<< orphan*/  radix__flush_all_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  radix__flush_tlb_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  radix__flush_tlb_pwc_range_psize (struct mm_struct*,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  radix__flush_tlb_range_psize (struct mm_struct*,unsigned long,unsigned long,int) ; 
 int radix_get_mmu_psize (int) ; 

void radix__tlb_flush(struct mmu_gather *tlb)
{
	int psize = 0;
	struct mm_struct *mm = tlb->mm;
	int page_size = tlb->page_size;
	unsigned long start = tlb->start;
	unsigned long end = tlb->end;

	/*
	 * if page size is not something we understand, do a full mm flush
	 *
	 * A "fullmm" flush must always do a flush_all_mm (RIC=2) flush
	 * that flushes the process table entry cache upon process teardown.
	 * See the comment for radix in arch_exit_mmap().
	 */
	if (tlb->fullmm) {
		__flush_all_mm(mm, true);
#if defined(CONFIG_TRANSPARENT_HUGEPAGE) || defined(CONFIG_HUGETLB_PAGE)
	} else if (mm_tlb_flush_nested(mm)) {
		/*
		 * If there is a concurrent invalidation that is clearing ptes,
		 * then it's possible this invalidation will miss one of those
		 * cleared ptes and miss flushing the TLB. If this invalidate
		 * returns before the other one flushes TLBs, that can result
		 * in it returning while there are still valid TLBs inside the
		 * range to be invalidated.
		 *
		 * See mm/memory.c:tlb_finish_mmu() for more details.
		 *
		 * The solution to this is ensure the entire range is always
		 * flushed here. The problem for powerpc is that the flushes
		 * are page size specific, so this "forced flush" would not
		 * do the right thing if there are a mix of page sizes in
		 * the range to be invalidated. So use __flush_tlb_range
		 * which invalidates all possible page sizes in the range.
		 *
		 * PWC flush probably is not be required because the core code
		 * shouldn't free page tables in this path, but accounting
		 * for the possibility makes us a bit more robust.
		 *
		 * need_flush_all is an uncommon case because page table
		 * teardown should be done with exclusive locks held (but
		 * after locks are dropped another invalidate could come
		 * in), it could be optimized further if necessary.
		 */
		if (!tlb->need_flush_all)
			__radix__flush_tlb_range(mm, start, end, true);
		else
			radix__flush_all_mm(mm);
#endif
	} else if ( (psize = radix_get_mmu_psize(page_size)) == -1) {
		if (!tlb->need_flush_all)
			radix__flush_tlb_mm(mm);
		else
			radix__flush_all_mm(mm);
	} else {
		if (!tlb->need_flush_all)
			radix__flush_tlb_range_psize(mm, start, end, psize);
		else
			radix__flush_tlb_pwc_range_psize(mm, start, end, psize);
	}
	tlb->need_flush_all = 0;
}