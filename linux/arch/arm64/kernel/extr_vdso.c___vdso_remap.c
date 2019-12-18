#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vm_special_mapping {int dummy; } ;
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; } ;
typedef  enum arch_vdso_type { ____Placeholder_arch_vdso_type } arch_vdso_type ;
struct TYPE_8__ {TYPE_2__* mm; } ;
struct TYPE_7__ {unsigned long vdso_code_end; unsigned long vdso_code_start; } ;
struct TYPE_5__ {void* vdso; } ;
struct TYPE_6__ {TYPE_1__ context; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_4__* current ; 
 TYPE_3__* vdso_lookup ; 

__attribute__((used)) static int __vdso_remap(enum arch_vdso_type arch_index,
			const struct vm_special_mapping *sm,
			struct vm_area_struct *new_vma)
{
	unsigned long new_size = new_vma->vm_end - new_vma->vm_start;
	unsigned long vdso_size = vdso_lookup[arch_index].vdso_code_end -
				  vdso_lookup[arch_index].vdso_code_start;

	if (vdso_size != new_size)
		return -EINVAL;

	current->mm->context.vdso = (void *)new_vma->vm_start;

	return 0;
}