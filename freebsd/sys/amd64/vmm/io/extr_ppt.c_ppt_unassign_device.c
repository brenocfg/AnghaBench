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
struct vm {int dummy; } ;
struct pptdev {struct vm* vm; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  iommu_remove_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_rid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_restore_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_save_state (int /*<<< orphan*/ ) ; 
 struct pptdev* ppt_find (int,int,int) ; 
 int /*<<< orphan*/  ppt_pci_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppt_teardown_msi (struct pptdev*) ; 
 int /*<<< orphan*/  ppt_teardown_msix (struct pptdev*) ; 
 int /*<<< orphan*/  ppt_unmap_mmio (struct vm*,struct pptdev*) ; 
 int /*<<< orphan*/  vm_iommu_domain (struct vm*) ; 

int
ppt_unassign_device(struct vm *vm, int bus, int slot, int func)
{
	struct pptdev *ppt;

	ppt = ppt_find(bus, slot, func);
	if (ppt != NULL) {
		/*
		 * If this device is not owned by this 'vm' then bail out.
		 */
		if (ppt->vm != vm)
			return (EBUSY);

		pci_save_state(ppt->dev);
		ppt_pci_reset(ppt->dev);
		pci_restore_state(ppt->dev);
		ppt_unmap_mmio(vm, ppt);
		ppt_teardown_msi(ppt);
		ppt_teardown_msix(ppt);
		iommu_remove_device(vm_iommu_domain(vm), pci_get_rid(ppt->dev));
		ppt->vm = NULL;
		return (0);
	}
	return (ENOENT);
}