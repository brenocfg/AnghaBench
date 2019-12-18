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
struct mm_walk {int /*<<< orphan*/  mm; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  _PAGE_INVALID ; 
 int /*<<< orphan*/  __pte (int /*<<< orphan*/ ) ; 
 scalar_t__ is_zero_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptep_xchg_direct (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __zap_zero_pages(pmd_t *pmd, unsigned long start,
			   unsigned long end, struct mm_walk *walk)
{
	unsigned long addr;

	for (addr = start; addr != end; addr += PAGE_SIZE) {
		pte_t *ptep;
		spinlock_t *ptl;

		ptep = pte_offset_map_lock(walk->mm, pmd, addr, &ptl);
		if (is_zero_pfn(pte_pfn(*ptep)))
			ptep_xchg_direct(walk->mm, addr, ptep, __pte(_PAGE_INVALID));
		pte_unmap_unlock(ptep, ptl);
	}
	return 0;
}