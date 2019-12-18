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
struct kvm_mmu_memory_cache {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  clear_page (int /*<<< orphan*/ *) ; 
 scalar_t__ invalid_pte_table ; 
 void* mmu_memory_cache_alloc (struct kvm_mmu_memory_cache*) ; 
 int /*<<< orphan*/  pgd_index (unsigned long) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_init (unsigned long,unsigned long) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_populate_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pte_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_populate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static pte_t *kvm_mips_walk_pgd(pgd_t *pgd, struct kvm_mmu_memory_cache *cache,
				unsigned long addr)
{
	pud_t *pud;
	pmd_t *pmd;

	pgd += pgd_index(addr);
	if (pgd_none(*pgd)) {
		/* Not used on MIPS yet */
		BUG();
		return NULL;
	}
	pud = pud_offset(pgd, addr);
	if (pud_none(*pud)) {
		pmd_t *new_pmd;

		if (!cache)
			return NULL;
		new_pmd = mmu_memory_cache_alloc(cache);
		pmd_init((unsigned long)new_pmd,
			 (unsigned long)invalid_pte_table);
		pud_populate(NULL, pud, new_pmd);
	}
	pmd = pmd_offset(pud, addr);
	if (pmd_none(*pmd)) {
		pte_t *new_pte;

		if (!cache)
			return NULL;
		new_pte = mmu_memory_cache_alloc(cache);
		clear_page(new_pte);
		pmd_populate_kernel(NULL, pmd, new_pte);
	}
	return pte_offset(pmd, addr);
}