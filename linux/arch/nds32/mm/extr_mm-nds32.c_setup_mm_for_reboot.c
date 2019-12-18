#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_6__ {TYPE_1__* mm; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pgd; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pgd; } ;

/* Variables and functions */
 int PGDIR_SHIFT ; 
 int USER_PTRS_PER_PGD ; 
 int /*<<< orphan*/  __pmd (unsigned long) ; 
 TYPE_3__* current ; 
 TYPE_2__ init_mm ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void setup_mm_for_reboot(char mode)
{
	unsigned long pmdval;
	pgd_t *pgd;
	pmd_t *pmd;
	int i;

	if (current->mm && current->mm->pgd)
		pgd = current->mm->pgd;
	else
		pgd = init_mm.pgd;

	for (i = 0; i < USER_PTRS_PER_PGD; i++) {
		pmdval = (i << PGDIR_SHIFT);
		pmd = pmd_offset(pgd + i, i << PGDIR_SHIFT);
		set_pmd(pmd, __pmd(pmdval));
	}
}