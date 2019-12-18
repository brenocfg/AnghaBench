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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  scalar_t__ vm_offset_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAPDEV_ASSERTVALID ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ VM_MIN_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int pmap_change_props_locked (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
pmap_change_prot(vm_offset_t va, vm_size_t size, vm_prot_t prot)
{
	int error;

	/* Only supported within the kernel map. */
	if (va < VM_MIN_KERNEL_ADDRESS)
		return (EINVAL);

	PMAP_LOCK(kernel_pmap);
	error = pmap_change_props_locked(va, size, prot, -1,
	    MAPDEV_ASSERTVALID);
	PMAP_UNLOCK(kernel_pmap);
	return (error);
}