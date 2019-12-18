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
struct vm_area_struct {int /*<<< orphan*/  vm_flags; int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; struct vm_area_struct* vm_next; } ;
struct TYPE_3__ {int uses_skeys; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; int /*<<< orphan*/  def_flags; TYPE_1__ context; struct vm_area_struct* mmap; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MADV_UNMERGEABLE ; 
 int /*<<< orphan*/  TASK_SIZE ; 
 int /*<<< orphan*/  VM_MERGEABLE ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_skey_walk_ops ; 
 scalar_t__ ksm_madvise (struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mm_uses_skeys (struct mm_struct*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walk_page_range (struct mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int s390_enable_skey(void)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;
	int rc = 0;

	down_write(&mm->mmap_sem);
	if (mm_uses_skeys(mm))
		goto out_up;

	mm->context.uses_skeys = 1;
	for (vma = mm->mmap; vma; vma = vma->vm_next) {
		if (ksm_madvise(vma, vma->vm_start, vma->vm_end,
				MADV_UNMERGEABLE, &vma->vm_flags)) {
			mm->context.uses_skeys = 0;
			rc = -ENOMEM;
			goto out_up;
		}
	}
	mm->def_flags &= ~VM_MERGEABLE;

	walk_page_range(mm, 0, TASK_SIZE, &enable_skey_walk_ops, NULL);

out_up:
	up_write(&mm->mmap_sem);
	return rc;
}