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
struct pg_state {int /*<<< orphan*/  seq; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PPC_64K_PAGES ; 
 unsigned long H_PAGE_4K_PFN ; 
 unsigned long H_PAGE_COMBO ; 
 unsigned long H_PAGE_HASHPTE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int PTRS_PER_PTE ; 
 unsigned long VMALLOC_END ; 
 int hpte_find (struct pg_state*,unsigned long,unsigned long) ; 
 unsigned long mmu_io_psize ; 
 unsigned long mmu_vmalloc_psize ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 

__attribute__((used)) static void walk_pte(struct pg_state *st, pmd_t *pmd, unsigned long start)
{
	pte_t *pte = pte_offset_kernel(pmd, 0);
	unsigned long addr, pteval, psize;
	int i, status;

	for (i = 0; i < PTRS_PER_PTE; i++, pte++) {
		addr = start + i * PAGE_SIZE;
		pteval = pte_val(*pte);

		if (addr < VMALLOC_END)
			psize = mmu_vmalloc_psize;
		else
			psize = mmu_io_psize;

		/* check for secret 4K mappings */
		if (IS_ENABLED(CONFIG_PPC_64K_PAGES) &&
		    ((pteval & H_PAGE_COMBO) == H_PAGE_COMBO ||
		     (pteval & H_PAGE_4K_PFN) == H_PAGE_4K_PFN))
			psize = mmu_io_psize;

		/* check for hashpte */
		status = hpte_find(st, addr, psize);

		if (((pteval & H_PAGE_HASHPTE) != H_PAGE_HASHPTE)
				&& (status != -1)) {
		/* found a hpte that is not in the linux page tables */
			seq_printf(st->seq, "page probably bolted before linux"
				" pagetables were set: addr:%lx, pteval:%lx\n",
				addr, pteval);
		}
	}
}