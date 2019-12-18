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
struct pptdev {int /*<<< orphan*/  dev; struct vm* vm; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  iommu_add_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_rid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_restore_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_save_state (int /*<<< orphan*/ ) ; 
 struct pptdev* ppt_find (int,int,int) ; 
 int /*<<< orphan*/  ppt_pci_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_iommu_domain (struct vm*) ; 

int
ppt_assign_device(struct vm *vm, int bus, int slot, int func)
{
	struct pptdev *ppt;

	ppt = ppt_find(bus, slot, func);
	if (ppt != NULL) {
		/*
		 * If this device is owned by a different VM then we
		 * cannot change its owner.
		 */
		if (ppt->vm != NULL && ppt->vm != vm)
			return (EBUSY);

		pci_save_state(ppt->dev);
		ppt_pci_reset(ppt->dev);
		pci_restore_state(ppt->dev);
		ppt->vm = vm;
		iommu_add_device(vm_iommu_domain(vm), pci_get_rid(ppt->dev));
		return (0);
	}
	return (ENOENT);
}