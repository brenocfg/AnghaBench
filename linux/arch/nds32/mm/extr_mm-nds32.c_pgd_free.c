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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  NR_PAGETABLE ; 
 int /*<<< orphan*/  dec_zone_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_dec_nr_ptes (struct mm_struct*) ; 
 int /*<<< orphan*/  pmd_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_free (struct mm_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_free (struct mm_struct*,struct page*) ; 
 int /*<<< orphan*/  virt_to_page (unsigned long*) ; 

void pgd_free(struct mm_struct *mm, pgd_t * pgd)
{
	pmd_t *pmd;
	struct page *pte;

	if (!pgd)
		return;

	pmd = (pmd_t *) pgd;
	if (pmd_none(*pmd))
		goto free;
	if (pmd_bad(*pmd)) {
		pmd_ERROR(*pmd);
		pmd_clear(pmd);
		goto free;
	}

	pte = pmd_page(*pmd);
	pmd_clear(pmd);
	dec_zone_page_state(virt_to_page((unsigned long *)pgd), NR_PAGETABLE);
	pte_free(mm, pte);
	mm_dec_nr_ptes(mm);
	pmd_free(mm, pmd);
free:
	free_pages((unsigned long)pgd, 0);
}