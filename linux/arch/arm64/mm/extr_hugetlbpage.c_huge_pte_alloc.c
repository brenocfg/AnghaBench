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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARCH_WANT_HUGE_PMD_SHARE ; 
 unsigned long CONT_PMD_SIZE ; 
 unsigned long CONT_PTE_SIZE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned long PMD_SIZE ; 
 unsigned long PUD_SIZE ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (unsigned long) ; 
 int /*<<< orphan*/ * huge_pmd_share (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * pmd_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pte_alloc_map (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pud_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 

pte_t *huge_pte_alloc(struct mm_struct *mm,
		      unsigned long addr, unsigned long sz)
{
	pgd_t *pgdp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep = NULL;

	pgdp = pgd_offset(mm, addr);
	pudp = pud_alloc(mm, pgdp, addr);
	if (!pudp)
		return NULL;

	if (sz == PUD_SIZE) {
		ptep = (pte_t *)pudp;
	} else if (sz == (CONT_PTE_SIZE)) {
		pmdp = pmd_alloc(mm, pudp, addr);

		WARN_ON(addr & (sz - 1));
		/*
		 * Note that if this code were ever ported to the
		 * 32-bit arm platform then it will cause trouble in
		 * the case where CONFIG_HIGHPTE is set, since there
		 * will be no pte_unmap() to correspond with this
		 * pte_alloc_map().
		 */
		ptep = pte_alloc_map(mm, pmdp, addr);
	} else if (sz == PMD_SIZE) {
		if (IS_ENABLED(CONFIG_ARCH_WANT_HUGE_PMD_SHARE) &&
		    pud_none(READ_ONCE(*pudp)))
			ptep = huge_pmd_share(mm, addr, pudp);
		else
			ptep = (pte_t *)pmd_alloc(mm, pudp, addr);
	} else if (sz == (CONT_PMD_SIZE)) {
		pmdp = pmd_alloc(mm, pudp, addr);
		WARN_ON(addr & (sz - 1));
		return (pte_t *)pmdp;
	}

	return ptep;
}