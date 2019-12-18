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
struct page {int dummy; } ;
struct mmu_gather {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  paravirt_release_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paravirt_tlb_remove_table (struct mmu_gather*,struct page*) ; 
 int /*<<< orphan*/  pgtable_pte_page_dtor (struct page*) ; 

void ___pte_free_tlb(struct mmu_gather *tlb, struct page *pte)
{
	pgtable_pte_page_dtor(pte);
	paravirt_release_pte(page_to_pfn(pte));
	paravirt_tlb_remove_table(tlb, pte);
}