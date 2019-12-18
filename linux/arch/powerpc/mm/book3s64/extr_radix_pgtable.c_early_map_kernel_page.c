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
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned int PMD_SIZE ; 
 int /*<<< orphan*/  PMD_TABLE_SIZE ; 
 unsigned int PUD_SIZE ; 
 int /*<<< orphan*/  PUD_TABLE_SIZE ; 
 void* early_alloc_pgtable (int /*<<< orphan*/ ,int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/  pgd_populate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_populate_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmdp_ptep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_populate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static int early_map_kernel_page(unsigned long ea, unsigned long pa,
			  pgprot_t flags,
			  unsigned int map_page_size,
			  int nid,
			  unsigned long region_start, unsigned long region_end)
{
	unsigned long pfn = pa >> PAGE_SHIFT;
	pgd_t *pgdp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	pgdp = pgd_offset_k(ea);
	if (pgd_none(*pgdp)) {
		pudp = early_alloc_pgtable(PUD_TABLE_SIZE, nid,
						region_start, region_end);
		pgd_populate(&init_mm, pgdp, pudp);
	}
	pudp = pud_offset(pgdp, ea);
	if (map_page_size == PUD_SIZE) {
		ptep = (pte_t *)pudp;
		goto set_the_pte;
	}
	if (pud_none(*pudp)) {
		pmdp = early_alloc_pgtable(PMD_TABLE_SIZE, nid,
						region_start, region_end);
		pud_populate(&init_mm, pudp, pmdp);
	}
	pmdp = pmd_offset(pudp, ea);
	if (map_page_size == PMD_SIZE) {
		ptep = pmdp_ptep(pmdp);
		goto set_the_pte;
	}
	if (!pmd_present(*pmdp)) {
		ptep = early_alloc_pgtable(PAGE_SIZE, nid,
						region_start, region_end);
		pmd_populate_kernel(&init_mm, pmdp, ptep);
	}
	ptep = pte_offset_kernel(pmdp, ea);

set_the_pte:
	set_pte_at(&init_mm, ea, ptep, pfn_pte(pfn, flags));
	smp_wmb();
	return 0;
}