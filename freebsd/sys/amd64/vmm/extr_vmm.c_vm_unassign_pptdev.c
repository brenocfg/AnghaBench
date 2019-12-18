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

/* Variables and functions */
 scalar_t__ ppt_assigned_devices (struct vm*) ; 
 int ppt_unassign_device (struct vm*,int,int,int) ; 
 int /*<<< orphan*/  vm_iommu_unmap (struct vm*) ; 

int
vm_unassign_pptdev(struct vm *vm, int bus, int slot, int func)
{
	int error;

	error = ppt_unassign_device(vm, bus, slot, func);
	if (error)
		return (error);

	if (ppt_assigned_devices(vm) == 0)
		vm_iommu_unmap(vm);

	return (0);
}