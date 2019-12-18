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
struct vm_area_struct {int vm_flags; } ;
struct page {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long DCACHE_ALIAS_MASK ; 
 int /*<<< orphan*/  PG_arch_1 ; 
 int /*<<< orphan*/  PageReserved (struct page*) ; 
 unsigned long TLBTEMP_BASE_1 ; 
 int VM_EXEC ; 
 int /*<<< orphan*/  __flush_dcache_page (unsigned long) ; 
 int /*<<< orphan*/  __flush_invalidate_dcache_page_alias (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  __invalidate_icache_page (unsigned long) ; 
 int /*<<< orphan*/  __invalidate_icache_page_alias (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_tlb_page (struct vm_area_struct*,unsigned long) ; 
 scalar_t__ kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 unsigned long page_to_phys (struct page*) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
update_mmu_cache(struct vm_area_struct * vma, unsigned long addr, pte_t *ptep)
{
	unsigned long pfn = pte_pfn(*ptep);
	struct page *page;

	if (!pfn_valid(pfn))
		return;

	page = pfn_to_page(pfn);

	/* Invalidate old entry in TLBs */

	flush_tlb_page(vma, addr);

#if (DCACHE_WAY_SIZE > PAGE_SIZE)

	if (!PageReserved(page) && test_bit(PG_arch_1, &page->flags)) {
		unsigned long phys = page_to_phys(page);
		unsigned long tmp;

		tmp = TLBTEMP_BASE_1 + (phys & DCACHE_ALIAS_MASK);
		__flush_invalidate_dcache_page_alias(tmp, phys);
		tmp = TLBTEMP_BASE_1 + (addr & DCACHE_ALIAS_MASK);
		__flush_invalidate_dcache_page_alias(tmp, phys);
		__invalidate_icache_page_alias(tmp, phys);

		clear_bit(PG_arch_1, &page->flags);
	}
#else
	if (!PageReserved(page) && !test_bit(PG_arch_1, &page->flags)
	    && (vma->vm_flags & VM_EXEC) != 0) {
		unsigned long paddr = (unsigned long)kmap_atomic(page);
		__flush_dcache_page(paddr);
		__invalidate_icache_page(paddr);
		set_bit(PG_arch_1, &page->flags);
		kunmap_atomic((void *)paddr);
	}
#endif
}