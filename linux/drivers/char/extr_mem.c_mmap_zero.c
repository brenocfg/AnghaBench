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
struct vm_area_struct {int vm_flags; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int VM_SHARED ; 
 int shmem_zero_setup (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vma_set_anonymous (struct vm_area_struct*) ; 

__attribute__((used)) static int mmap_zero(struct file *file, struct vm_area_struct *vma)
{
#ifndef CONFIG_MMU
	return -ENOSYS;
#endif
	if (vma->vm_flags & VM_SHARED)
		return shmem_zero_setup(vma);
	vma_set_anonymous(vma);
	return 0;
}