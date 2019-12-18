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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_PGTABLE_USER ; 
 int /*<<< orphan*/  __GFP_ACCOUNT ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  free_pmds (struct mm_struct*,int /*<<< orphan*/ **,int) ; 
 struct mm_struct init_mm ; 
 int /*<<< orphan*/  mm_inc_nr_pmds (struct mm_struct*) ; 
 int /*<<< orphan*/  pgtable_pmd_page_ctor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int preallocate_pmds(struct mm_struct *mm, pmd_t *pmds[], int count)
{
	int i;
	bool failed = false;
	gfp_t gfp = GFP_PGTABLE_USER;

	if (mm == &init_mm)
		gfp &= ~__GFP_ACCOUNT;

	for (i = 0; i < count; i++) {
		pmd_t *pmd = (pmd_t *)__get_free_page(gfp);
		if (!pmd)
			failed = true;
		if (pmd && !pgtable_pmd_page_ctor(virt_to_page(pmd))) {
			free_page((unsigned long)pmd);
			pmd = NULL;
			failed = true;
		}
		if (pmd)
			mm_inc_nr_pmds(mm);
		pmds[i] = pmd;
	}

	if (failed) {
		free_pmds(mm, pmds, count);
		return -ENOMEM;
	}

	return 0;
}