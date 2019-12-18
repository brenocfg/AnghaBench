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
struct vm_area_struct {int vm_flags; TYPE_2__* vm_mm; } ;
struct TYPE_3__ {scalar_t__ execute_only_pkey; } ;
struct TYPE_4__ {TYPE_1__ context; } ;

/* Variables and functions */
 int VM_EXEC ; 
 int VM_READ ; 
 int VM_WRITE ; 
 scalar_t__ vma_pkey (struct vm_area_struct*) ; 

__attribute__((used)) static inline bool vma_is_pkey_exec_only(struct vm_area_struct *vma)
{
	/* Do this check first since the vm_flags should be hot */
	if ((vma->vm_flags & (VM_READ | VM_WRITE | VM_EXEC)) != VM_EXEC)
		return false;
	if (vma_pkey(vma) != vma->vm_mm->context.execute_only_pkey)
		return false;

	return true;
}