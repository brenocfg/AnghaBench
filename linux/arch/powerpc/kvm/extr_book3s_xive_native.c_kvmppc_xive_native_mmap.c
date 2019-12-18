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
struct vm_area_struct {scalar_t__ vm_pgoff; int vm_flags; TYPE_1__* vm_file; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/ * vm_ops; } ;
struct kvmppc_xive {int /*<<< orphan*/  mapping; } ;
struct kvm_device {struct kvmppc_xive* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  f_mapping; } ;

/* Variables and functions */
 int EINVAL ; 
 int KVMPPC_XIVE_NR_IRQS ; 
 scalar_t__ KVM_XIVE_ESB_PAGE_OFFSET ; 
 scalar_t__ KVM_XIVE_TIMA_PAGE_OFFSET ; 
 int VM_IO ; 
 int VM_PFNMAP ; 
 int /*<<< orphan*/  pgprot_noncached_wc (int /*<<< orphan*/ ) ; 
 int vma_pages (struct vm_area_struct*) ; 
 int /*<<< orphan*/  xive_native_esb_vmops ; 
 int /*<<< orphan*/  xive_native_tima_vmops ; 

__attribute__((used)) static int kvmppc_xive_native_mmap(struct kvm_device *dev,
				   struct vm_area_struct *vma)
{
	struct kvmppc_xive *xive = dev->private;

	/* We only allow mappings at fixed offset for now */
	if (vma->vm_pgoff == KVM_XIVE_TIMA_PAGE_OFFSET) {
		if (vma_pages(vma) > 4)
			return -EINVAL;
		vma->vm_ops = &xive_native_tima_vmops;
	} else if (vma->vm_pgoff == KVM_XIVE_ESB_PAGE_OFFSET) {
		if (vma_pages(vma) > KVMPPC_XIVE_NR_IRQS * 2)
			return -EINVAL;
		vma->vm_ops = &xive_native_esb_vmops;
	} else {
		return -EINVAL;
	}

	vma->vm_flags |= VM_IO | VM_PFNMAP;
	vma->vm_page_prot = pgprot_noncached_wc(vma->vm_page_prot);

	/*
	 * Grab the KVM device file address_space to be able to clear
	 * the ESB pages mapping when a device is passed-through into
	 * the guest.
	 */
	xive->mapping = vma->vm_file->f_mapping;
	return 0;
}