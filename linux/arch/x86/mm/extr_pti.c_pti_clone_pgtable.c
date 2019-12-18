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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;
typedef  enum pti_clone_level { ____Placeholder_pti_clone_level } pti_clone_level ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned long PMD_MASK ; 
 scalar_t__ PMD_SIZE ; 
 int PTI_CLONE_PMD ; 
 int PTI_CLONE_PTE ; 
 unsigned long PUD_MASK ; 
 scalar_t__ PUD_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (unsigned long) ; 
 int /*<<< orphan*/  X86_FEATURE_PGE ; 
 int /*<<< orphan*/  _PAGE_GLOBAL ; 
 int _PAGE_PRESENT ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int p4d_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int pmd_flags (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_large (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_set_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pte_flags (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_set_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pti_user_pagetable_walk_pmd (unsigned long) ; 
 int /*<<< orphan*/ * pti_user_pagetable_walk_pte (unsigned long) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long round_up (unsigned long,scalar_t__) ; 

__attribute__((used)) static void
pti_clone_pgtable(unsigned long start, unsigned long end,
		  enum pti_clone_level level)
{
	unsigned long addr;

	/*
	 * Clone the populated PMDs which cover start to end. These PMD areas
	 * can have holes.
	 */
	for (addr = start; addr < end;) {
		pte_t *pte, *target_pte;
		pmd_t *pmd, *target_pmd;
		pgd_t *pgd;
		p4d_t *p4d;
		pud_t *pud;

		/* Overflow check */
		if (addr < start)
			break;

		pgd = pgd_offset_k(addr);
		if (WARN_ON(pgd_none(*pgd)))
			return;
		p4d = p4d_offset(pgd, addr);
		if (WARN_ON(p4d_none(*p4d)))
			return;

		pud = pud_offset(p4d, addr);
		if (pud_none(*pud)) {
			WARN_ON_ONCE(addr & ~PUD_MASK);
			addr = round_up(addr + 1, PUD_SIZE);
			continue;
		}

		pmd = pmd_offset(pud, addr);
		if (pmd_none(*pmd)) {
			WARN_ON_ONCE(addr & ~PMD_MASK);
			addr = round_up(addr + 1, PMD_SIZE);
			continue;
		}

		if (pmd_large(*pmd) || level == PTI_CLONE_PMD) {
			target_pmd = pti_user_pagetable_walk_pmd(addr);
			if (WARN_ON(!target_pmd))
				return;

			/*
			 * Only clone present PMDs.  This ensures only setting
			 * _PAGE_GLOBAL on present PMDs.  This should only be
			 * called on well-known addresses anyway, so a non-
			 * present PMD would be a surprise.
			 */
			if (WARN_ON(!(pmd_flags(*pmd) & _PAGE_PRESENT)))
				return;

			/*
			 * Setting 'target_pmd' below creates a mapping in both
			 * the user and kernel page tables.  It is effectively
			 * global, so set it as global in both copies.  Note:
			 * the X86_FEATURE_PGE check is not _required_ because
			 * the CPU ignores _PAGE_GLOBAL when PGE is not
			 * supported.  The check keeps consistentency with
			 * code that only set this bit when supported.
			 */
			if (boot_cpu_has(X86_FEATURE_PGE))
				*pmd = pmd_set_flags(*pmd, _PAGE_GLOBAL);

			/*
			 * Copy the PMD.  That is, the kernelmode and usermode
			 * tables will share the last-level page tables of this
			 * address range
			 */
			*target_pmd = *pmd;

			addr += PMD_SIZE;

		} else if (level == PTI_CLONE_PTE) {

			/* Walk the page-table down to the pte level */
			pte = pte_offset_kernel(pmd, addr);
			if (pte_none(*pte)) {
				addr += PAGE_SIZE;
				continue;
			}

			/* Only clone present PTEs */
			if (WARN_ON(!(pte_flags(*pte) & _PAGE_PRESENT)))
				return;

			/* Allocate PTE in the user page-table */
			target_pte = pti_user_pagetable_walk_pte(addr);
			if (WARN_ON(!target_pte))
				return;

			/* Set GLOBAL bit in both PTEs */
			if (boot_cpu_has(X86_FEATURE_PGE))
				*pte = pte_set_flags(*pte, _PAGE_GLOBAL);

			/* Clone the PTE */
			*target_pte = *pte;

			addr += PAGE_SIZE;

		} else {
			BUG();
		}
	}
}