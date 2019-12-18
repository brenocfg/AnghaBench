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

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
#define  HTLB_16G_INDEX 132 
#define  HTLB_16M_INDEX 131 
 int /*<<< orphan*/  H_16G_CACHE_INDEX ; 
 int /*<<< orphan*/  H_16M_CACHE_INDEX ; 
 int /*<<< orphan*/  PGT_CACHE (int /*<<< orphan*/ ) ; 
#define  PMD_INDEX 130 
#define  PTE_INDEX 129 
 int /*<<< orphan*/  PUD_CACHE_INDEX ; 
#define  PUD_INDEX 128 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pmd_fragment_free (void*) ; 
 int /*<<< orphan*/  pte_fragment_free (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pgtable_free(void *table, int index)
{
	switch (index) {
	case PTE_INDEX:
		pte_fragment_free(table, 0);
		break;
	case PMD_INDEX:
		pmd_fragment_free(table);
		break;
	case PUD_INDEX:
		kmem_cache_free(PGT_CACHE(PUD_CACHE_INDEX), table);
		break;
#if defined(CONFIG_PPC_4K_PAGES) && defined(CONFIG_HUGETLB_PAGE)
		/* 16M hugepd directory at pud level */
	case HTLB_16M_INDEX:
		BUILD_BUG_ON(H_16M_CACHE_INDEX <= 0);
		kmem_cache_free(PGT_CACHE(H_16M_CACHE_INDEX), table);
		break;
		/* 16G hugepd directory at the pgd level */
	case HTLB_16G_INDEX:
		BUILD_BUG_ON(H_16G_CACHE_INDEX <= 0);
		kmem_cache_free(PGT_CACHE(H_16G_CACHE_INDEX), table);
		break;
#endif
		/* We don't free pgd table via RCU callback */
	default:
		BUG();
	}
}