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
struct vma_data {int type; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; } ;
struct vm_area_struct {scalar_t__ vm_pgoff; int vm_flags; int /*<<< orphan*/ * vm_ops; int /*<<< orphan*/  vm_page_prot; struct vma_data* vm_private_data; int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; } ;
struct file {int dummy; } ;
typedef  enum mspec_page_type { ____Placeholder_mspec_page_type } mspec_page_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MSPEC_UNCACHED ; 
 int PAGE_SIZE ; 
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int VM_IO ; 
 int VM_PFNMAP ; 
 int VM_SHARED ; 
 int VM_WRITE ; 
 struct vma_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mspec_vm_ops ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int vma_pages (struct vm_area_struct*) ; 
 struct vma_data* vzalloc (int) ; 

__attribute__((used)) static int
mspec_mmap(struct file *file, struct vm_area_struct *vma,
					enum mspec_page_type type)
{
	struct vma_data *vdata;
	int pages, vdata_size;

	if (vma->vm_pgoff != 0)
		return -EINVAL;

	if ((vma->vm_flags & VM_SHARED) == 0)
		return -EINVAL;

	if ((vma->vm_flags & VM_WRITE) == 0)
		return -EPERM;

	pages = vma_pages(vma);
	vdata_size = sizeof(struct vma_data) + pages * sizeof(long);
	if (vdata_size <= PAGE_SIZE)
		vdata = kzalloc(vdata_size, GFP_KERNEL);
	else
		vdata = vzalloc(vdata_size);
	if (!vdata)
		return -ENOMEM;

	vdata->vm_start = vma->vm_start;
	vdata->vm_end = vma->vm_end;
	vdata->type = type;
	spin_lock_init(&vdata->lock);
	refcount_set(&vdata->refcnt, 1);
	vma->vm_private_data = vdata;

	vma->vm_flags |= VM_IO | VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP;
	if (vdata->type == MSPEC_UNCACHED)
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_ops = &mspec_vm_ops;

	return 0;
}