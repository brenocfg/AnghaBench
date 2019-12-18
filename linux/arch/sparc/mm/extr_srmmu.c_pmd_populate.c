#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_3__ {int /*<<< orphan*/ * pmdv; } ;
typedef  TYPE_1__ pmd_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PTRS_PER_PTE ; 
 unsigned long SRMMU_ET_PTD ; 
 int SRMMU_REAL_PTRS_PER_PTE ; 
 int /*<<< orphan*/  __pte (unsigned long) ; 
 int page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void pmd_populate(struct mm_struct *mm, pmd_t *pmdp, struct page *ptep)
{
	unsigned long ptp;	/* Physical address, shifted right by 4 */
	int i;

	ptp = page_to_pfn(ptep) << (PAGE_SHIFT-4);	/* watch for overflow */
	for (i = 0; i < PTRS_PER_PTE/SRMMU_REAL_PTRS_PER_PTE; i++) {
		set_pte((pte_t *)&pmdp->pmdv[i], __pte(SRMMU_ET_PTD | ptp));
		ptp += (SRMMU_REAL_PTRS_PER_PTE * sizeof(pte_t) >> 4);
	}
}