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
struct page {int dummy; } ;
struct multicall_space {int /*<<< orphan*/  mc; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  enum pt_level { ____Placeholder_pt_level } pt_level ;

/* Variables and functions */
 int /*<<< orphan*/  MMUEXT_PIN_L1_TABLE ; 
 int /*<<< orphan*/  MULTI_update_va_mapping (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_KERNEL_RO ; 
 int PT_PGD ; 
 int PT_PTE ; 
 scalar_t__ PageHighMem (struct page*) ; 
 unsigned int TestSetPagePinned (struct page*) ; 
 int /*<<< orphan*/  UVMF_TLB_FLUSH ; 
 struct multicall_space __xen_mc_entry (int /*<<< orphan*/ ) ; 
 void* lowmem_page_address (struct page*) ; 
 unsigned long page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_do_pin (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  xen_mc_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xen_pte_lock (struct page*,struct mm_struct*) ; 
 int /*<<< orphan*/  xen_pte_unlock ; 

__attribute__((used)) static int xen_pin_page(struct mm_struct *mm, struct page *page,
			enum pt_level level)
{
	unsigned pgfl = TestSetPagePinned(page);
	int flush;

	if (pgfl)
		flush = 0;		/* already pinned */
	else if (PageHighMem(page))
		/* kmaps need flushing if we found an unpinned
		   highpage */
		flush = 1;
	else {
		void *pt = lowmem_page_address(page);
		unsigned long pfn = page_to_pfn(page);
		struct multicall_space mcs = __xen_mc_entry(0);
		spinlock_t *ptl;

		flush = 0;

		/*
		 * We need to hold the pagetable lock between the time
		 * we make the pagetable RO and when we actually pin
		 * it.  If we don't, then other users may come in and
		 * attempt to update the pagetable by writing it,
		 * which will fail because the memory is RO but not
		 * pinned, so Xen won't do the trap'n'emulate.
		 *
		 * If we're using split pte locks, we can't hold the
		 * entire pagetable's worth of locks during the
		 * traverse, because we may wrap the preempt count (8
		 * bits).  The solution is to mark RO and pin each PTE
		 * page while holding the lock.  This means the number
		 * of locks we end up holding is never more than a
		 * batch size (~32 entries, at present).
		 *
		 * If we're not using split pte locks, we needn't pin
		 * the PTE pages independently, because we're
		 * protected by the overall pagetable lock.
		 */
		ptl = NULL;
		if (level == PT_PTE)
			ptl = xen_pte_lock(page, mm);

		MULTI_update_va_mapping(mcs.mc, (unsigned long)pt,
					pfn_pte(pfn, PAGE_KERNEL_RO),
					level == PT_PGD ? UVMF_TLB_FLUSH : 0);

		if (ptl) {
			xen_do_pin(MMUEXT_PIN_L1_TABLE, pfn);

			/* Queue a deferred unlock for when this batch
			   is completed. */
			xen_mc_callback(xen_pte_unlock, ptl);
		}
	}

	return flush;
}