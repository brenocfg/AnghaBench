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
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  hugepd_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMD_SHIFT ; 
 unsigned long PUD_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __hugepd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_hugepd_range (struct mmu_gather*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int hugepd_shift (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_hugepd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_dec_nr_pmds (int /*<<< orphan*/ ) ; 
 unsigned long pmd_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pmd_free_tlb (struct mmu_gather*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hugetlb_free_pmd_range(struct mmu_gather *tlb, pud_t *pud,
				   unsigned long addr, unsigned long end,
				   unsigned long floor, unsigned long ceiling)
{
	pmd_t *pmd;
	unsigned long next;
	unsigned long start;

	start = addr;
	do {
		unsigned long more;

		pmd = pmd_offset(pud, addr);
		next = pmd_addr_end(addr, end);
		if (!is_hugepd(__hugepd(pmd_val(*pmd)))) {
			/*
			 * if it is not hugepd pointer, we should already find
			 * it cleared.
			 */
			WARN_ON(!pmd_none_or_clear_bad(pmd));
			continue;
		}
		/*
		 * Increment next by the size of the huge mapping since
		 * there may be more than one entry at this level for a
		 * single hugepage, but all of them point to
		 * the same kmem cache that holds the hugepte.
		 */
		more = addr + (1 << hugepd_shift(*(hugepd_t *)pmd));
		if (more > next)
			next = more;

		free_hugepd_range(tlb, (hugepd_t *)pmd, PMD_SHIFT,
				  addr, next, floor, ceiling);
	} while (addr = next, addr != end);

	start &= PUD_MASK;
	if (start < floor)
		return;
	if (ceiling) {
		ceiling &= PUD_MASK;
		if (!ceiling)
			return;
	}
	if (end - 1 > ceiling - 1)
		return;

	pmd = pmd_offset(pud, start);
	pud_clear(pud);
	pmd_free_tlb(tlb, pmd, start);
	mm_dec_nr_pmds(tlb->mm);
}