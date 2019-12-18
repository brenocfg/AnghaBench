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
struct mm_struct {int /*<<< orphan*/  page_table_lock; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  hugepd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int PGDIR_SHIFT ; 
 unsigned int PMD_SHIFT ; 
 unsigned int PUD_SHIFT ; 
 unsigned int __ffs (unsigned long) ; 
 scalar_t__ __hugepte_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ hugepd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hugepd_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hugepte_offset (int /*<<< orphan*/ ,unsigned long,unsigned int) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * pmd_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pmd_lockptr (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pud_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pud_lockptr (struct mm_struct*,int /*<<< orphan*/ *) ; 

pte_t *huge_pte_alloc(struct mm_struct *mm, unsigned long addr, unsigned long sz)
{
	pgd_t *pg;
	pud_t *pu;
	pmd_t *pm;
	hugepd_t *hpdp = NULL;
	unsigned pshift = __ffs(sz);
	unsigned pdshift = PGDIR_SHIFT;
	spinlock_t *ptl;

	addr &= ~(sz-1);
	pg = pgd_offset(mm, addr);

#ifdef CONFIG_PPC_BOOK3S_64
	if (pshift == PGDIR_SHIFT)
		/* 16GB huge page */
		return (pte_t *) pg;
	else if (pshift > PUD_SHIFT) {
		/*
		 * We need to use hugepd table
		 */
		ptl = &mm->page_table_lock;
		hpdp = (hugepd_t *)pg;
	} else {
		pdshift = PUD_SHIFT;
		pu = pud_alloc(mm, pg, addr);
		if (!pu)
			return NULL;
		if (pshift == PUD_SHIFT)
			return (pte_t *)pu;
		else if (pshift > PMD_SHIFT) {
			ptl = pud_lockptr(mm, pu);
			hpdp = (hugepd_t *)pu;
		} else {
			pdshift = PMD_SHIFT;
			pm = pmd_alloc(mm, pu, addr);
			if (!pm)
				return NULL;
			if (pshift == PMD_SHIFT)
				/* 16MB hugepage */
				return (pte_t *)pm;
			else {
				ptl = pmd_lockptr(mm, pm);
				hpdp = (hugepd_t *)pm;
			}
		}
	}
#else
	if (pshift >= PGDIR_SHIFT) {
		ptl = &mm->page_table_lock;
		hpdp = (hugepd_t *)pg;
	} else {
		pdshift = PUD_SHIFT;
		pu = pud_alloc(mm, pg, addr);
		if (!pu)
			return NULL;
		if (pshift >= PUD_SHIFT) {
			ptl = pud_lockptr(mm, pu);
			hpdp = (hugepd_t *)pu;
		} else {
			pdshift = PMD_SHIFT;
			pm = pmd_alloc(mm, pu, addr);
			if (!pm)
				return NULL;
			ptl = pmd_lockptr(mm, pm);
			hpdp = (hugepd_t *)pm;
		}
	}
#endif
	if (!hpdp)
		return NULL;

	BUG_ON(!hugepd_none(*hpdp) && !hugepd_ok(*hpdp));

	if (hugepd_none(*hpdp) && __hugepte_alloc(mm, hpdp, addr,
						  pdshift, pshift, ptl))
		return NULL;

	return hugepte_offset(*hpdp, addr, pdshift);
}