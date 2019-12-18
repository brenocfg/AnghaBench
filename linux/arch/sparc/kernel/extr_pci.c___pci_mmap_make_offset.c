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
struct vm_area_struct {unsigned long vm_pgoff; unsigned long vm_end; unsigned long vm_start; } ;
struct resource {int flags; unsigned long end; unsigned long start; } ;
struct pci_dev {int class; struct resource* resource; } ;
typedef  unsigned long resource_size_t ;
typedef  enum pci_mmap_state { ____Placeholder_pci_mmap_state } pci_mmap_state ;

/* Variables and functions */
 int EINVAL ; 
 int IORESOURCE_IO ; 
 int IORESOURCE_MEM ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int PCI_CLASS_BRIDGE_HOST ; 
 int PCI_ROM_RESOURCE ; 
 int __pci_mmap_make_offset_bus (struct pci_dev*,struct vm_area_struct*,int) ; 
 int pci_mmap_io ; 
 int pci_mmap_mem ; 

__attribute__((used)) static int __pci_mmap_make_offset(struct pci_dev *pdev,
				  struct vm_area_struct *vma,
				  enum pci_mmap_state mmap_state)
{
	unsigned long user_paddr, user_size;
	int i, err;

	/* First compute the physical address in vma->vm_pgoff,
	 * making sure the user offset is within range in the
	 * appropriate PCI space.
	 */
	err = __pci_mmap_make_offset_bus(pdev, vma, mmap_state);
	if (err)
		return err;

	/* If this is a mapping on a host bridge, any address
	 * is OK.
	 */
	if ((pdev->class >> 8) == PCI_CLASS_BRIDGE_HOST)
		return err;

	/* Otherwise make sure it's in the range for one of the
	 * device's resources.
	 */
	user_paddr = vma->vm_pgoff << PAGE_SHIFT;
	user_size = vma->vm_end - vma->vm_start;

	for (i = 0; i <= PCI_ROM_RESOURCE; i++) {
		struct resource *rp = &pdev->resource[i];
		resource_size_t aligned_end;

		/* Active? */
		if (!rp->flags)
			continue;

		/* Same type? */
		if (i == PCI_ROM_RESOURCE) {
			if (mmap_state != pci_mmap_mem)
				continue;
		} else {
			if ((mmap_state == pci_mmap_io &&
			     (rp->flags & IORESOURCE_IO) == 0) ||
			    (mmap_state == pci_mmap_mem &&
			     (rp->flags & IORESOURCE_MEM) == 0))
				continue;
		}

		/* Align the resource end to the next page address.
		 * PAGE_SIZE intentionally added instead of (PAGE_SIZE - 1),
		 * because actually we need the address of the next byte
		 * after rp->end.
		 */
		aligned_end = (rp->end + PAGE_SIZE) & PAGE_MASK;

		if ((rp->start <= user_paddr) &&
		    (user_paddr + user_size) <= aligned_end)
			break;
	}

	if (i > PCI_ROM_RESOURCE)
		return -EINVAL;

	return 0;
}