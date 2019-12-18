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
struct vm_area_struct {size_t vm_end; size_t vm_start; int vm_pgoff; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/ * vm_ops; } ;
struct file {int dummy; } ;
typedef  int phys_addr_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENOSYS ; 
 int EPERM ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  mmap_mem_ops ; 
 int /*<<< orphan*/  phys_mem_access_prot (struct file*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phys_mem_access_prot_allowed (struct file*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  private_mapping_ok (struct vm_area_struct*) ; 
 int /*<<< orphan*/  range_is_allowed (int,size_t) ; 
 scalar_t__ remap_pfn_range (struct vm_area_struct*,size_t,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valid_mmap_phys_addr_range (int,size_t) ; 

__attribute__((used)) static int mmap_mem(struct file *file, struct vm_area_struct *vma)
{
	size_t size = vma->vm_end - vma->vm_start;
	phys_addr_t offset = (phys_addr_t)vma->vm_pgoff << PAGE_SHIFT;

	/* Does it even fit in phys_addr_t? */
	if (offset >> PAGE_SHIFT != vma->vm_pgoff)
		return -EINVAL;

	/* It's illegal to wrap around the end of the physical address space. */
	if (offset + (phys_addr_t)size - 1 < offset)
		return -EINVAL;

	if (!valid_mmap_phys_addr_range(vma->vm_pgoff, size))
		return -EINVAL;

	if (!private_mapping_ok(vma))
		return -ENOSYS;

	if (!range_is_allowed(vma->vm_pgoff, size))
		return -EPERM;

	if (!phys_mem_access_prot_allowed(file, vma->vm_pgoff, size,
						&vma->vm_page_prot))
		return -EINVAL;

	vma->vm_page_prot = phys_mem_access_prot(file, vma->vm_pgoff,
						 size,
						 vma->vm_page_prot);

	vma->vm_ops = &mmap_mem_ops;

	/* Remap-pfn-range will mark the range VM_IO */
	if (remap_pfn_range(vma,
			    vma->vm_start,
			    vma->vm_pgoff,
			    size,
			    vma->vm_page_prot)) {
		return -EAGAIN;
	}
	return 0;
}