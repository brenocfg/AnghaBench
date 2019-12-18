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
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  hugepd_t ;

/* Variables and functions */
 int /*<<< orphan*/  PGDIR_SHIFT ; 
 int /*<<< orphan*/  __hugepd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_hugepd_range (struct mmu_gather*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int hugepd_shift (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hugetlb_free_pud_range (struct mmu_gather*,int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  is_hugepd (int /*<<< orphan*/ ) ; 
 unsigned long pgd_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pgd_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgd_offset (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pgd_val (int /*<<< orphan*/ ) ; 

void hugetlb_free_pgd_range(struct mmu_gather *tlb,
			    unsigned long addr, unsigned long end,
			    unsigned long floor, unsigned long ceiling)
{
	pgd_t *pgd;
	unsigned long next;

	/*
	 * Because there are a number of different possible pagetable
	 * layouts for hugepage ranges, we limit knowledge of how
	 * things should be laid out to the allocation path
	 * (huge_pte_alloc(), above).  Everything else works out the
	 * structure as it goes from information in the hugepd
	 * pointers.  That means that we can't here use the
	 * optimization used in the normal page free_pgd_range(), of
	 * checking whether we're actually covering a large enough
	 * range to have to do anything at the top level of the walk
	 * instead of at the bottom.
	 *
	 * To make sense of this, you should probably go read the big
	 * block comment at the top of the normal free_pgd_range(),
	 * too.
	 */

	do {
		next = pgd_addr_end(addr, end);
		pgd = pgd_offset(tlb->mm, addr);
		if (!is_hugepd(__hugepd(pgd_val(*pgd)))) {
			if (pgd_none_or_clear_bad(pgd))
				continue;
			hugetlb_free_pud_range(tlb, pgd, addr, next, floor, ceiling);
		} else {
			unsigned long more;
			/*
			 * Increment next by the size of the huge mapping since
			 * there may be more than one entry at the pgd level
			 * for a single hugepage, but all of them point to the
			 * same kmem cache that holds the hugepte.
			 */
			more = addr + (1 << hugepd_shift(*(hugepd_t *)pgd));
			if (more > next)
				next = more;

			free_hugepd_range(tlb, (hugepd_t *)pgd, PGDIR_SHIFT,
					  addr, next, floor, ceiling);
		}
	} while (addr = next, addr != end);
}