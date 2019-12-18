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

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ pmd_page_vaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ try_to_free_pte_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool unmap_pte_range(pmd_t *pmd, unsigned long start, unsigned long end)
{
	pte_t *pte = pte_offset_kernel(pmd, start);

	while (start < end) {
		set_pte(pte, __pte(0));

		start += PAGE_SIZE;
		pte++;
	}

	if (try_to_free_pte_page((pte_t *)pmd_page_vaddr(*pmd))) {
		pmd_clear(pmd);
		return true;
	}
	return false;
}