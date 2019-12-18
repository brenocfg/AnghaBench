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
struct vm_special_mapping {int dummy; } ;
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; TYPE_2__* vm_mm; } ;
struct TYPE_6__ {TYPE_2__* mm; } ;
struct TYPE_4__ {unsigned long vdso_base; scalar_t__ compat_mm; } ;
struct TYPE_5__ {TYPE_1__ context; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 TYPE_3__* current ; 
 unsigned long vdso32_pages ; 
 unsigned long vdso64_pages ; 

__attribute__((used)) static int vdso_mremap(const struct vm_special_mapping *sm,
		       struct vm_area_struct *vma)
{
	unsigned long vdso_pages;

	vdso_pages = vdso64_pages;
#ifdef CONFIG_COMPAT_VDSO
	if (vma->vm_mm->context.compat_mm)
		vdso_pages = vdso32_pages;
#endif

	if ((vdso_pages << PAGE_SHIFT) != vma->vm_end - vma->vm_start)
		return -EINVAL;

	if (WARN_ON_ONCE(current->mm != vma->vm_mm))
		return -EFAULT;

	current->mm->context.vdso_base = vma->vm_start;
	return 0;
}