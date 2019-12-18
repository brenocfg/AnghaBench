#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {struct vm_area_struct* vm_next; int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; } ;
struct mm_struct {struct vm_area_struct* mmap; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  fix_range (struct mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void force_flush_all(void)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma = mm->mmap;

	while (vma != NULL) {
		fix_range(mm, vma->vm_start, vma->vm_end, 1);
		vma = vma->vm_next;
	}
}