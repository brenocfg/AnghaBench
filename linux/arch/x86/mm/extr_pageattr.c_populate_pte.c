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
struct cpa_data {int /*<<< orphan*/  pfn; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  pfn_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_clear_protnone_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void populate_pte(struct cpa_data *cpa,
			 unsigned long start, unsigned long end,
			 unsigned num_pages, pmd_t *pmd, pgprot_t pgprot)
{
	pte_t *pte;

	pte = pte_offset_kernel(pmd, start);

	pgprot = pgprot_clear_protnone_bits(pgprot);

	while (num_pages-- && start < end) {
		set_pte(pte, pfn_pte(cpa->pfn, pgprot));

		start	 += PAGE_SIZE;
		cpa->pfn++;
		pte++;
	}
}