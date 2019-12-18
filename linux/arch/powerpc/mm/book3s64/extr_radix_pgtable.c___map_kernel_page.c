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
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 unsigned long MAX_EA_BITS_PER_CONTEXT ; 
 unsigned long PAGE_SHIFT ; 
 unsigned int PMD_SIZE ; 
 unsigned int PUD_SIZE ; 
 unsigned long RADIX_KERN_MAP_SIZE ; 
 scalar_t__ RADIX_PGTABLE_RANGE ; 
 scalar_t__ TASK_SIZE_USER64 ; 
 int early_map_kernel_page (unsigned long,unsigned long,int /*<<< orphan*/ ,unsigned int,int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/ * pmd_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pmdp_ptep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pte_alloc_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pud_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slab_is_available () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __map_kernel_page(unsigned long ea, unsigned long pa,
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
	/*
	 * Make sure task size is correct as per the max adddr
	 */
	BUILD_BUG_ON(TASK_SIZE_USER64 > RADIX_PGTABLE_RANGE);

#ifdef CONFIG_PPC_64K_PAGES
	BUILD_BUG_ON(RADIX_KERN_MAP_SIZE != (1UL << MAX_EA_BITS_PER_CONTEXT));
#endif

	if (unlikely(!slab_is_available()))
		return early_map_kernel_page(ea, pa, flags, map_page_size,
						nid, region_start, region_end);

	/*
	 * Should make page table allocation functions be able to take a
	 * node, so we can place kernel page tables on the right nodes after
	 * boot.
	 */
	pgdp = pgd_offset_k(ea);
	pudp = pud_alloc(&init_mm, pgdp, ea);
	if (!pudp)
		return -ENOMEM;
	if (map_page_size == PUD_SIZE) {
		ptep = (pte_t *)pudp;
		goto set_the_pte;
	}
	pmdp = pmd_alloc(&init_mm, pudp, ea);
	if (!pmdp)
		return -ENOMEM;
	if (map_page_size == PMD_SIZE) {
		ptep = pmdp_ptep(pmdp);
		goto set_the_pte;
	}
	ptep = pte_alloc_kernel(pmdp, ea);
	if (!ptep)
		return -ENOMEM;

set_the_pte:
	set_pte_at(&init_mm, ea, ptep, pfn_pte(pfn, flags));
	smp_wmb();
	return 0;
}