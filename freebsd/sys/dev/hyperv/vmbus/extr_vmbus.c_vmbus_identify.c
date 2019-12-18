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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CPUID_HV_MSR_SYNIC ; 
 scalar_t__ VM_GUEST_HV ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int hyperv_features ; 
 scalar_t__ vm_guest ; 

__attribute__((used)) static void
vmbus_identify(driver_t *driver, device_t parent)
{

	if (device_get_unit(parent) != 0 || vm_guest != VM_GUEST_HV ||
	    (hyperv_features & CPUID_HV_MSR_SYNIC) == 0)
		return;
	device_add_child(parent, "vmbus", -1);
}