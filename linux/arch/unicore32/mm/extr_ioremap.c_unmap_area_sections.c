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
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 scalar_t__ PGDIR_SIZE ; 
 int PMD_TYPE_MASK ; 
 int PMD_TYPE_TABLE ; 
 int SZ_4M ; 
 int /*<<< orphan*/  flush_cache_vunmap (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_tlb_kernel_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/  pmd_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_page_vaddr (int /*<<< orphan*/ ) ; 
 int pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unmap_area_sections(unsigned long virt, unsigned long size)
{
	unsigned long addr = virt, end = virt + (size & ~(SZ_4M - 1));
	pgd_t *pgd;

	flush_cache_vunmap(addr, end);
	pgd = pgd_offset_k(addr);
	do {
		pmd_t pmd, *pmdp = pmd_offset((pud_t *)pgd, addr);

		pmd = *pmdp;
		if (!pmd_none(pmd)) {
			/*
			 * Clear the PMD from the page table, and
			 * increment the kvm sequence so others
			 * notice this change.
			 *
			 * Note: this is still racy on SMP machines.
			 */
			pmd_clear(pmdp);

			/*
			 * Free the page table, if there was one.
			 */
			if ((pmd_val(pmd) & PMD_TYPE_MASK) == PMD_TYPE_TABLE)
				pte_free_kernel(&init_mm, pmd_page_vaddr(pmd));
		}

		addr += PGDIR_SIZE;
		pgd++;
	} while (addr < end);

	flush_tlb_kernel_range(virt, end);
}