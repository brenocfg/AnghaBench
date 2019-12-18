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
struct vm_area_struct {scalar_t__ vm_mm; int vm_flags; } ;
struct page {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_2__ {scalar_t__ active_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDS32_SR_TLB_VPN ; 
 int /*<<< orphan*/  PG_dcache_dirty ; 
 int VM_EXEC ; 
 int /*<<< orphan*/  __nds32__isb () ; 
 int /*<<< orphan*/  __nds32__mtsr_dsb (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __nds32__tlbop_rwr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_cache_wbinval_page (unsigned long,int) ; 
 TYPE_1__* current ; 
 scalar_t__ kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void update_mmu_cache(struct vm_area_struct *vma, unsigned long addr,
		      pte_t * pte)
{
	struct page *page;
	unsigned long pfn = pte_pfn(*pte);
	unsigned long flags;

	if (!pfn_valid(pfn))
		return;

	if (vma->vm_mm == current->active_mm) {
		local_irq_save(flags);
		__nds32__mtsr_dsb(addr, NDS32_SR_TLB_VPN);
		__nds32__tlbop_rwr(*pte);
		__nds32__isb();
		local_irq_restore(flags);
	}
	page = pfn_to_page(pfn);

	if ((test_and_clear_bit(PG_dcache_dirty, &page->flags)) ||
	    (vma->vm_flags & VM_EXEC)) {
		unsigned long kaddr;
		local_irq_save(flags);
		kaddr = (unsigned long)kmap_atomic(page);
		cpu_cache_wbinval_page(kaddr, vma->vm_flags & VM_EXEC);
		kunmap_atomic((void *)kaddr);
		local_irq_restore(flags);
	}
}