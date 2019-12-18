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

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/ * find_init_mm_pte (unsigned long,int*) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long eeh_token_to_phys(unsigned long token)
{
	pte_t *ptep;
	unsigned long pa;
	int hugepage_shift;

	/*
	 * We won't find hugepages here(this is iomem). Hence we are not
	 * worried about _PAGE_SPLITTING/collapse. Also we will not hit
	 * page table free, because of init_mm.
	 */
	ptep = find_init_mm_pte(token, &hugepage_shift);
	if (!ptep)
		return token;

	pa = pte_pfn(*ptep);

	/* On radix we can do hugepage mappings for io, so handle that */
	if (hugepage_shift) {
		pa <<= hugepage_shift;
		pa |= token & ((1ul << hugepage_shift) - 1);
	} else {
		pa <<= PAGE_SHIFT;
		pa |= token & (PAGE_SIZE - 1);
	}

	return pa;
}