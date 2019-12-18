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

/* Variables and functions */
 unsigned long PGDIR_SHIFT ; 
 int PMD_SHIFT ; 
 int PTRS_PER_PMD ; 
 int PTRS_PER_PUD ; 
 unsigned long PUD_SHIFT ; 
 int USER_PTRS_PER_PGD ; 
 int /*<<< orphan*/  pgd_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pte_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_mips_emul_free_gva_pt(pgd_t *pgd)
{
	/* Don't free host kernel page tables copied from init_mm.pgd */
	const unsigned long end = 0x80000000;
	unsigned long pgd_va, pud_va, pmd_va;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	int i, j, k;

	for (i = 0; i < USER_PTRS_PER_PGD; i++) {
		if (pgd_none(pgd[i]))
			continue;

		pgd_va = (unsigned long)i << PGDIR_SHIFT;
		if (pgd_va >= end)
			break;
		pud = pud_offset(pgd + i, 0);
		for (j = 0; j < PTRS_PER_PUD; j++) {
			if (pud_none(pud[j]))
				continue;

			pud_va = pgd_va | ((unsigned long)j << PUD_SHIFT);
			if (pud_va >= end)
				break;
			pmd = pmd_offset(pud + j, 0);
			for (k = 0; k < PTRS_PER_PMD; k++) {
				if (pmd_none(pmd[k]))
					continue;

				pmd_va = pud_va | (k << PMD_SHIFT);
				if (pmd_va >= end)
					break;
				pte = pte_offset(pmd + k, 0);
				pte_free_kernel(NULL, pte);
			}
			pmd_free(NULL, pmd);
		}
		pud_free(NULL, pud);
	}
	pgd_free(NULL, pgd);
}