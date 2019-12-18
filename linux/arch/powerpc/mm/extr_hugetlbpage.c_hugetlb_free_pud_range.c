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
struct mmu_gather {int /*<<< orphan*/  mm; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  hugepd_t ;

/* Variables and functions */
 unsigned long PGDIR_MASK ; 
 int /*<<< orphan*/  PUD_SHIFT ; 
 int /*<<< orphan*/  __hugepd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_hugepd_range (struct mmu_gather*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int hugepd_shift (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hugetlb_free_pmd_range (struct mmu_gather*,int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  is_hugepd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_dec_nr_puds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_clear (int /*<<< orphan*/ *) ; 
 unsigned long pud_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pud_free_tlb (struct mmu_gather*,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pud_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hugetlb_free_pud_range(struct mmu_gather *tlb, pgd_t *pgd,
				   unsigned long addr, unsigned long end,
				   unsigned long floor, unsigned long ceiling)
{
	pud_t *pud;
	unsigned long next;
	unsigned long start;

	start = addr;
	do {
		pud = pud_offset(pgd, addr);
		next = pud_addr_end(addr, end);
		if (!is_hugepd(__hugepd(pud_val(*pud)))) {
			if (pud_none_or_clear_bad(pud))
				continue;
			hugetlb_free_pmd_range(tlb, pud, addr, next, floor,
					       ceiling);
		} else {
			unsigned long more;
			/*
			 * Increment next by the size of the huge mapping since
			 * there may be more than one entry at this level for a
			 * single hugepage, but all of them point to
			 * the same kmem cache that holds the hugepte.
			 */
			more = addr + (1 << hugepd_shift(*(hugepd_t *)pud));
			if (more > next)
				next = more;

			free_hugepd_range(tlb, (hugepd_t *)pud, PUD_SHIFT,
					  addr, next, floor, ceiling);
		}
	} while (addr = next, addr != end);

	start &= PGDIR_MASK;
	if (start < floor)
		return;
	if (ceiling) {
		ceiling &= PGDIR_MASK;
		if (!ceiling)
			return;
	}
	if (end - 1 > ceiling - 1)
		return;

	pud = pud_offset(pgd, start);
	pgd_clear(pgd);
	pud_free_tlb(tlb, pud, start);
	mm_dec_nr_puds(tlb->mm);
}