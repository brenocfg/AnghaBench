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
typedef  int /*<<< orphan*/  hugepd_t ;

/* Variables and functions */
 unsigned int PGDIR_SHIFT ; 
 unsigned int PMD_SHIFT ; 
 unsigned int PUD_SHIFT ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __hugepd (int /*<<< orphan*/ ) ; 
 unsigned int hugepd_shift (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hugepte_offset (int /*<<< orphan*/ ,unsigned long,unsigned int) ; 
 scalar_t__ is_hugepd (int /*<<< orphan*/ ) ; 
 int pgd_index (unsigned long) ; 
 scalar_t__ pgd_is_leaf (int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_val (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_devmap (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_is_leaf (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_is_serializing (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pud_is_leaf (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_val (int /*<<< orphan*/ ) ; 

pte_t *__find_linux_pte(pgd_t *pgdir, unsigned long ea,
			bool *is_thp, unsigned *hpage_shift)
{
	pgd_t pgd, *pgdp;
	pud_t pud, *pudp;
	pmd_t pmd, *pmdp;
	pte_t *ret_pte;
	hugepd_t *hpdp = NULL;
	unsigned pdshift = PGDIR_SHIFT;

	if (hpage_shift)
		*hpage_shift = 0;

	if (is_thp)
		*is_thp = false;

	pgdp = pgdir + pgd_index(ea);
	pgd  = READ_ONCE(*pgdp);
	/*
	 * Always operate on the local stack value. This make sure the
	 * value don't get updated by a parallel THP split/collapse,
	 * page fault or a page unmap. The return pte_t * is still not
	 * stable. So should be checked there for above conditions.
	 */
	if (pgd_none(pgd))
		return NULL;

	if (pgd_is_leaf(pgd)) {
		ret_pte = (pte_t *)pgdp;
		goto out;
	}

	if (is_hugepd(__hugepd(pgd_val(pgd)))) {
		hpdp = (hugepd_t *)&pgd;
		goto out_huge;
	}

	/*
	 * Even if we end up with an unmap, the pgtable will not
	 * be freed, because we do an rcu free and here we are
	 * irq disabled
	 */
	pdshift = PUD_SHIFT;
	pudp = pud_offset(&pgd, ea);
	pud  = READ_ONCE(*pudp);

	if (pud_none(pud))
		return NULL;

	if (pud_is_leaf(pud)) {
		ret_pte = (pte_t *)pudp;
		goto out;
	}

	if (is_hugepd(__hugepd(pud_val(pud)))) {
		hpdp = (hugepd_t *)&pud;
		goto out_huge;
	}

	pdshift = PMD_SHIFT;
	pmdp = pmd_offset(&pud, ea);
	pmd  = READ_ONCE(*pmdp);

	/*
	 * A hugepage collapse is captured by this condition, see
	 * pmdp_collapse_flush.
	 */
	if (pmd_none(pmd))
		return NULL;

#ifdef CONFIG_PPC_BOOK3S_64
	/*
	 * A hugepage split is captured by this condition, see
	 * pmdp_invalidate.
	 *
	 * Huge page modification can be caught here too.
	 */
	if (pmd_is_serializing(pmd))
		return NULL;
#endif

	if (pmd_trans_huge(pmd) || pmd_devmap(pmd)) {
		if (is_thp)
			*is_thp = true;
		ret_pte = (pte_t *)pmdp;
		goto out;
	}

	if (pmd_is_leaf(pmd)) {
		ret_pte = (pte_t *)pmdp;
		goto out;
	}

	if (is_hugepd(__hugepd(pmd_val(pmd)))) {
		hpdp = (hugepd_t *)&pmd;
		goto out_huge;
	}

	return pte_offset_kernel(&pmd, ea);

out_huge:
	if (!hpdp)
		return NULL;

	ret_pte = hugepte_offset(*hpdp, ea, pdshift);
	pdshift = hugepd_shift(*hpdp);
out:
	if (hpage_shift)
		*hpage_shift = pdshift;
	return ret_pte;
}