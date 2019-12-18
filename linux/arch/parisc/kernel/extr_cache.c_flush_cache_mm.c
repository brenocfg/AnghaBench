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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; int vm_flags; struct vm_area_struct* vm_next; } ;
struct mm_struct {scalar_t__ context; struct vm_area_struct* mmap; int /*<<< orphan*/ * pgd; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SMP ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PFN_PHYS (unsigned long) ; 
 int VM_EXEC ; 
 int /*<<< orphan*/  __flush_cache_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __purge_cache_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_irqs_disabled () ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 int /*<<< orphan*/  flush_tlb_all () ; 
 int /*<<< orphan*/  flush_tlb_page (struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  flush_tlb_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_user_dcache_range_asm (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_user_icache_range_asm (unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * get_ptep (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ mfsp (int) ; 
 scalar_t__ mm_total_size (struct mm_struct*) ; 
 scalar_t__ parisc_cache_flush_threshold ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (scalar_t__) ; 

void flush_cache_mm(struct mm_struct *mm)
{
	struct vm_area_struct *vma;
	pgd_t *pgd;

	/* Flushing the whole cache on each cpu takes forever on
	   rp3440, etc.  So, avoid it if the mm isn't too big.  */
	if ((!IS_ENABLED(CONFIG_SMP) || !arch_irqs_disabled()) &&
	    mm_total_size(mm) >= parisc_cache_flush_threshold) {
		if (mm->context)
			flush_tlb_all();
		flush_cache_all();
		return;
	}

	if (mm->context == mfsp(3)) {
		for (vma = mm->mmap; vma; vma = vma->vm_next) {
			flush_user_dcache_range_asm(vma->vm_start, vma->vm_end);
			if (vma->vm_flags & VM_EXEC)
				flush_user_icache_range_asm(vma->vm_start, vma->vm_end);
			flush_tlb_range(vma, vma->vm_start, vma->vm_end);
		}
		return;
	}

	pgd = mm->pgd;
	for (vma = mm->mmap; vma; vma = vma->vm_next) {
		unsigned long addr;

		for (addr = vma->vm_start; addr < vma->vm_end;
		     addr += PAGE_SIZE) {
			unsigned long pfn;
			pte_t *ptep = get_ptep(pgd, addr);
			if (!ptep)
				continue;
			pfn = pte_pfn(*ptep);
			if (!pfn_valid(pfn))
				continue;
			if (unlikely(mm->context)) {
				flush_tlb_page(vma, addr);
				__flush_cache_page(vma, addr, PFN_PHYS(pfn));
			} else {
				__purge_cache_page(vma, addr, PFN_PHYS(pfn));
			}
		}
	}
}