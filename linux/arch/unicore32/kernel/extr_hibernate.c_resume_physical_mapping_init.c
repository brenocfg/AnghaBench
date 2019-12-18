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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_KERNEL_EXEC ; 
 int /*<<< orphan*/  PAGE_OFFSET ; 
 int PTRS_PER_PGD ; 
 int PTRS_PER_PMD ; 
 int PTRS_PER_PTE ; 
 unsigned long max_low_pfn ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 int pgd_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * resume_one_md_table_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resume_one_page_table_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int resume_physical_mapping_init(pgd_t *pgd_base)
{
	unsigned long pfn;
	pgd_t *pgd;
	pmd_t *pmd;
	pte_t *pte;
	int pgd_idx, pmd_idx;

	pgd_idx = pgd_index(PAGE_OFFSET);
	pgd = pgd_base + pgd_idx;
	pfn = 0;

	for (; pgd_idx < PTRS_PER_PGD; pgd++, pgd_idx++) {
		pmd = resume_one_md_table_init(pgd);
		if (!pmd)
			return -ENOMEM;

		if (pfn >= max_low_pfn)
			continue;

		for (pmd_idx = 0; pmd_idx < PTRS_PER_PMD; pmd++, pmd_idx++) {
			pte_t *max_pte;

			if (pfn >= max_low_pfn)
				break;

			/* Map with normal page tables.
			 * NOTE: We can mark everything as executable here
			 */
			pte = resume_one_page_table_init(pmd);
			if (!pte)
				return -ENOMEM;

			max_pte = pte + PTRS_PER_PTE;
			for (; pte < max_pte; pte++, pfn++) {
				if (pfn >= max_low_pfn)
					break;

				set_pte(pte, pfn_pte(pfn, PAGE_KERNEL_EXEC));
			}
		}
	}

	return 0;
}