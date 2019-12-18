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
struct vm_area_struct {unsigned long vm_pgoff; unsigned long vm_end; unsigned long vm_start; } ;
struct TYPE_6__ {unsigned long start; } ;
struct pci_pbm_info {TYPE_3__ mem_space; TYPE_3__ io_space; } ;
struct TYPE_4__ {struct pci_pbm_info* host_controller; } ;
struct TYPE_5__ {TYPE_1__ archdata; } ;
struct pci_dev {TYPE_2__ dev; } ;
typedef  enum pci_mmap_state { ____Placeholder_pci_mmap_state } pci_mmap_state ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 int pci_mmap_io ; 
 unsigned long resource_size (TYPE_3__*) ; 

__attribute__((used)) static int __pci_mmap_make_offset_bus(struct pci_dev *pdev, struct vm_area_struct *vma,
				      enum pci_mmap_state mmap_state)
{
	struct pci_pbm_info *pbm = pdev->dev.archdata.host_controller;
	unsigned long space_size, user_offset, user_size;

	if (mmap_state == pci_mmap_io) {
		space_size = resource_size(&pbm->io_space);
	} else {
		space_size = resource_size(&pbm->mem_space);
	}

	/* Make sure the request is in range. */
	user_offset = vma->vm_pgoff << PAGE_SHIFT;
	user_size = vma->vm_end - vma->vm_start;

	if (user_offset >= space_size ||
	    (user_offset + user_size) > space_size)
		return -EINVAL;

	if (mmap_state == pci_mmap_io) {
		vma->vm_pgoff = (pbm->io_space.start +
				 user_offset) >> PAGE_SHIFT;
	} else {
		vma->vm_pgoff = (pbm->mem_space.start +
				 user_offset) >> PAGE_SHIFT;
	}

	return 0;
}