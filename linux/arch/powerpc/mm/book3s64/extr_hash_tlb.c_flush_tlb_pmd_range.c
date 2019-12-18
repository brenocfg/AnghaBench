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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned long H_PAGE_HASHPTE ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PMD_SIZE ; 
 int PTRS_PER_PTE ; 
 unsigned long _ALIGN_DOWN (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_enter_lazy_mmu_mode () ; 
 int /*<<< orphan*/  arch_leave_lazy_mmu_mode () ; 
 int /*<<< orphan*/  hpte_need_flush (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 

void flush_tlb_pmd_range(struct mm_struct *mm, pmd_t *pmd, unsigned long addr)
{
	pte_t *pte;
	pte_t *start_pte;
	unsigned long flags;

	addr = _ALIGN_DOWN(addr, PMD_SIZE);
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
	start_pte = pte_offset_map(pmd, addr);
	for (pte = start_pte; pte < start_pte + PTRS_PER_PTE; pte++) {
		unsigned long pteval = pte_val(*pte);
		if (pteval & H_PAGE_HASHPTE)
			hpte_need_flush(mm, addr, pte, pteval, 0);
		addr += PAGE_SIZE;
	}
	arch_leave_lazy_mmu_mode();
	local_irq_restore(flags);
}