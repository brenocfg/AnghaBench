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
struct mmu_gather {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  hugepd_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PPC_8xx ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PTE_INDEX_SIZE ; 
 int /*<<< orphan*/  __hugepd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_hugepd_cache_index (int) ; 
 int /*<<< orphan*/  hugepd_free (struct mmu_gather*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hugepd_page (int /*<<< orphan*/ ) ; 
 unsigned int hugepd_shift (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgtable_free_tlb (struct mmu_gather*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_hugepd_range(struct mmu_gather *tlb, hugepd_t *hpdp, int pdshift,
			      unsigned long start, unsigned long end,
			      unsigned long floor, unsigned long ceiling)
{
	pte_t *hugepte = hugepd_page(*hpdp);
	int i;

	unsigned long pdmask = ~((1UL << pdshift) - 1);
	unsigned int num_hugepd = 1;
	unsigned int shift = hugepd_shift(*hpdp);

	/* Note: On fsl the hpdp may be the first of several */
	if (shift > pdshift)
		num_hugepd = 1 << (shift - pdshift);

	start &= pdmask;
	if (start < floor)
		return;
	if (ceiling) {
		ceiling &= pdmask;
		if (! ceiling)
			return;
	}
	if (end - 1 > ceiling - 1)
		return;

	for (i = 0; i < num_hugepd; i++, hpdp++)
		*hpdp = __hugepd(0);

	if (shift >= pdshift)
		hugepd_free(tlb, hugepte);
	else if (IS_ENABLED(CONFIG_PPC_8xx))
		pgtable_free_tlb(tlb, hugepte,
				 get_hugepd_cache_index(PTE_INDEX_SIZE));
	else
		pgtable_free_tlb(tlb, hugepte,
				 get_hugepd_cache_index(pdshift - shift));
}