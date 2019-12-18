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
struct mm_struct {int /*<<< orphan*/  pgd; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long H_PAGE_HASHPTE ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned long _ALIGN_DOWN (unsigned long,scalar_t__) ; 
 unsigned long _ALIGN_UP (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  arch_enter_lazy_mmu_mode () ; 
 int /*<<< orphan*/  arch_leave_lazy_mmu_mode () ; 
 int /*<<< orphan*/ * find_current_mm_pte (int /*<<< orphan*/ ,unsigned long,int*,int*) ; 
 int /*<<< orphan*/  hpte_do_hugepage_flush (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  hpte_need_flush (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,unsigned long,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hugepage_invalidate (unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

void __flush_hash_table_range(struct mm_struct *mm, unsigned long start,
			      unsigned long end)
{
	bool is_thp;
	int hugepage_shift;
	unsigned long flags;

	start = _ALIGN_DOWN(start, PAGE_SIZE);
	end = _ALIGN_UP(end, PAGE_SIZE);

	BUG_ON(!mm->pgd);

	/*
	 * Note: Normally, we should only ever use a batch within a
	 * PTE locked section. This violates the rule, but will work
	 * since we don't actually modify the PTEs, we just flush the
	 * hash while leaving the PTEs intact (including their reference
	 * to being hashed). This is not the most performance oriented
	 * way to do things but is fine for our needs here.
	 */
	local_irq_save(flags);
	arch_enter_lazy_mmu_mode();
	for (; start < end; start += PAGE_SIZE) {
		pte_t *ptep = find_current_mm_pte(mm->pgd, start, &is_thp,
						  &hugepage_shift);
		unsigned long pte;

		if (ptep == NULL)
			continue;
		pte = pte_val(*ptep);
		if (is_thp)
			trace_hugepage_invalidate(start, pte);
		if (!(pte & H_PAGE_HASHPTE))
			continue;
		if (unlikely(is_thp))
			hpte_do_hugepage_flush(mm, start, (pmd_t *)ptep, pte);
		else
			hpte_need_flush(mm, start, ptep, pte, hugepage_shift);
	}
	arch_leave_lazy_mmu_mode();
	local_irq_restore(flags);
}