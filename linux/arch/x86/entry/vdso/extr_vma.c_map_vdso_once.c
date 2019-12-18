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
struct vm_area_struct {struct vm_area_struct* vm_next; } ;
struct vdso_image {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; struct vm_area_struct* mmap; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int EEXIST ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int map_vdso (struct vdso_image const*,unsigned long) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdso_mapping ; 
 scalar_t__ vma_is_special_mapping (struct vm_area_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vvar_mapping ; 

int map_vdso_once(const struct vdso_image *image, unsigned long addr)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;

	down_write(&mm->mmap_sem);
	/*
	 * Check if we have already mapped vdso blob - fail to prevent
	 * abusing from userspace install_speciall_mapping, which may
	 * not do accounting and rlimit right.
	 * We could search vma near context.vdso, but it's a slowpath,
	 * so let's explicitly check all VMAs to be completely sure.
	 */
	for (vma = mm->mmap; vma; vma = vma->vm_next) {
		if (vma_is_special_mapping(vma, &vdso_mapping) ||
				vma_is_special_mapping(vma, &vvar_mapping)) {
			up_write(&mm->mmap_sem);
			return -EEXIST;
		}
	}
	up_write(&mm->mmap_sem);

	return map_vdso(image, addr);
}