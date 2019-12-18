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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/ * vm_ops; int /*<<< orphan*/  vm_page_prot; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int VM_IO ; 
 int VM_PFNMAP ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spufs_signal1_mmap_vmops ; 

__attribute__((used)) static int spufs_signal1_mmap(struct file *file, struct vm_area_struct *vma)
{
	if (!(vma->vm_flags & VM_SHARED))
		return -EINVAL;

	vma->vm_flags |= VM_IO | VM_PFNMAP;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	vma->vm_ops = &spufs_signal1_mmap_vmops;
	return 0;
}