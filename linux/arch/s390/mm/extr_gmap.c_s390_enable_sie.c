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
struct TYPE_3__ {int has_pgste; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; TYPE_1__ context; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TASK_SIZE ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_alloc_pgste (struct mm_struct*) ; 
 scalar_t__ mm_has_pgste (struct mm_struct*) ; 
 int /*<<< orphan*/  thp_split_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walk_page_range (struct mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_zero_walk_ops ; 

int s390_enable_sie(void)
{
	struct mm_struct *mm = current->mm;

	/* Do we have pgstes? if yes, we are done */
	if (mm_has_pgste(mm))
		return 0;
	/* Fail if the page tables are 2K */
	if (!mm_alloc_pgste(mm))
		return -EINVAL;
	down_write(&mm->mmap_sem);
	mm->context.has_pgste = 1;
	/* split thp mappings and disable thp for future mappings */
	thp_split_mm(mm);
	walk_page_range(mm, 0, TASK_SIZE, &zap_zero_walk_ops, NULL);
	up_write(&mm->mmap_sem);
	return 0;
}