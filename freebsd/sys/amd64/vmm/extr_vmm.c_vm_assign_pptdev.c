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
typedef  int /*<<< orphan*/  vm_paddr_t ;
struct vm {int /*<<< orphan*/ * iommu; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * iommu_create_domain (int /*<<< orphan*/ ) ; 
 int ppt_assign_device (struct vm*,int,int,int) ; 
 scalar_t__ ppt_assigned_devices (struct vm*) ; 
 int /*<<< orphan*/  vm_iommu_map (struct vm*) ; 
 int /*<<< orphan*/  vmm_sysmem_maxaddr (struct vm*) ; 

int
vm_assign_pptdev(struct vm *vm, int bus, int slot, int func)
{
	int error;
	vm_paddr_t maxaddr;

	/* Set up the IOMMU to do the 'gpa' to 'hpa' translation */
	if (ppt_assigned_devices(vm) == 0) {
		KASSERT(vm->iommu == NULL,
		    ("vm_assign_pptdev: iommu must be NULL"));
		maxaddr = vmm_sysmem_maxaddr(vm);
		vm->iommu = iommu_create_domain(maxaddr);
		if (vm->iommu == NULL)
			return (ENXIO);
		vm_iommu_map(vm);
	}

	error = ppt_assign_device(vm, bus, slot, func);
	return (error);
}