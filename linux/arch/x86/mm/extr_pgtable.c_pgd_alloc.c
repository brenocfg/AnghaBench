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
struct mm_struct {int /*<<< orphan*/ * pgd; } ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int MAX_PREALLOCATED_PMDS ; 
 int MAX_PREALLOCATED_USER_PMDS ; 
 int /*<<< orphan*/  PREALLOCATED_PMDS ; 
 int /*<<< orphan*/  PREALLOCATED_USER_PMDS ; 
 int /*<<< orphan*/ * _pgd_alloc () ; 
 int /*<<< orphan*/  _pgd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pmds (struct mm_struct*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ paravirt_pgd_alloc (struct mm_struct*) ; 
 int /*<<< orphan*/  pgd_ctor (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_lock ; 
 int /*<<< orphan*/  pgd_prepopulate_pmd (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pgd_prepopulate_user_pmd (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ preallocate_pmds (struct mm_struct*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

pgd_t *pgd_alloc(struct mm_struct *mm)
{
	pgd_t *pgd;
	pmd_t *u_pmds[MAX_PREALLOCATED_USER_PMDS];
	pmd_t *pmds[MAX_PREALLOCATED_PMDS];

	pgd = _pgd_alloc();

	if (pgd == NULL)
		goto out;

	mm->pgd = pgd;

	if (preallocate_pmds(mm, pmds, PREALLOCATED_PMDS) != 0)
		goto out_free_pgd;

	if (preallocate_pmds(mm, u_pmds, PREALLOCATED_USER_PMDS) != 0)
		goto out_free_pmds;

	if (paravirt_pgd_alloc(mm) != 0)
		goto out_free_user_pmds;

	/*
	 * Make sure that pre-populating the pmds is atomic with
	 * respect to anything walking the pgd_list, so that they
	 * never see a partially populated pgd.
	 */
	spin_lock(&pgd_lock);

	pgd_ctor(mm, pgd);
	pgd_prepopulate_pmd(mm, pgd, pmds);
	pgd_prepopulate_user_pmd(mm, pgd, u_pmds);

	spin_unlock(&pgd_lock);

	return pgd;

out_free_user_pmds:
	free_pmds(mm, u_pmds, PREALLOCATED_USER_PMDS);
out_free_pmds:
	free_pmds(mm, pmds, PREALLOCATED_PMDS);
out_free_pgd:
	_pgd_free(pgd);
out:
	return NULL;
}