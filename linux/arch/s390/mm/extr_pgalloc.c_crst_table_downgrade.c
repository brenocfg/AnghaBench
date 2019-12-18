#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ asce_limit; int asce; } ;
struct mm_struct {int /*<<< orphan*/ * pgd; TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_4__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int _ASCE_TABLE_LENGTH ; 
 int _ASCE_TYPE_SEGMENT ; 
 int _ASCE_USER_BITS ; 
 scalar_t__ _REGION2_SIZE ; 
 scalar_t__ _REGION3_SIZE ; 
 int _REGION_ENTRY_ORIGIN ; 
 int __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __tlb_flush_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  clear_user_asce () ; 
 int /*<<< orphan*/  crst_table_free (struct mm_struct*,unsigned long*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  mm_dec_nr_pmds (struct mm_struct*) ; 
 int pgd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_user_asce (struct mm_struct*) ; 

void crst_table_downgrade(struct mm_struct *mm)
{
	pgd_t *pgd;

	/* downgrade should only happen from 3 to 2 levels (compat only) */
	VM_BUG_ON(mm->context.asce_limit != _REGION2_SIZE);

	if (current->active_mm == mm) {
		clear_user_asce();
		__tlb_flush_mm(mm);
	}

	pgd = mm->pgd;
	mm_dec_nr_pmds(mm);
	mm->pgd = (pgd_t *) (pgd_val(*pgd) & _REGION_ENTRY_ORIGIN);
	mm->context.asce_limit = _REGION3_SIZE;
	mm->context.asce = __pa(mm->pgd) | _ASCE_TABLE_LENGTH |
			   _ASCE_USER_BITS | _ASCE_TYPE_SEGMENT;
	crst_table_free(mm, (unsigned long *) pgd);

	if (current->active_mm == mm)
		set_user_asce(mm);
}