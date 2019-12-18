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
struct vm_area_struct {int vm_pgoff; } ;
struct resource {int flags; int /*<<< orphan*/  start; } ;
struct pci_dev {int /*<<< orphan*/  sysdata; int /*<<< orphan*/  bus; struct resource* resource; } ;
struct pci_bus_region {int start; } ;
struct kobject {int dummy; } ;
struct bin_attribute {struct resource* private; } ;
typedef  enum pci_mmap_state { ____Placeholder_pci_mmap_state } pci_mmap_state ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int IORESOURCE_MEM ; 
 int PAGE_SHIFT ; 
 int PCI_ROM_RESOURCE ; 
 int /*<<< orphan*/  __pci_mmap_fits (struct pci_dev*,int,struct vm_area_struct*,int) ; 
 int hose_mmap_page_range (int /*<<< orphan*/ ,struct vm_area_struct*,int,int) ; 
 scalar_t__ iomem_is_exclusive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_to_dev (struct kobject*) ; 
 int pci_mmap_io ; 
 int pci_mmap_mem ; 
 int /*<<< orphan*/  pcibios_resource_to_bus (int /*<<< orphan*/ ,struct pci_bus_region*,struct resource*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_mmap_resource(struct kobject *kobj,
			     struct bin_attribute *attr,
			     struct vm_area_struct *vma, int sparse)
{
	struct pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));
	struct resource *res = attr->private;
	enum pci_mmap_state mmap_type;
	struct pci_bus_region bar;
	int i;

	for (i = 0; i < PCI_ROM_RESOURCE; i++)
		if (res == &pdev->resource[i])
			break;
	if (i >= PCI_ROM_RESOURCE)
		return -ENODEV;

	if (res->flags & IORESOURCE_MEM && iomem_is_exclusive(res->start))
		return -EINVAL;

	if (!__pci_mmap_fits(pdev, i, vma, sparse))
		return -EINVAL;

	pcibios_resource_to_bus(pdev->bus, &bar, res);
	vma->vm_pgoff += bar.start >> (PAGE_SHIFT - (sparse ? 5 : 0));
	mmap_type = res->flags & IORESOURCE_MEM ? pci_mmap_mem : pci_mmap_io;

	return hose_mmap_page_range(pdev->sysdata, vma, mmap_type, sparse);
}