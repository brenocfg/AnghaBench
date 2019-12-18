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

/* Variables and functions */
 int xen_has_pv_devices () ; 
 scalar_t__ xen_hvm_domain () ; 
 int xen_platform_pci_unplug ; 

__attribute__((used)) static bool __xen_has_pv_device(int state)
{
	/* HVM domains might or might not */
	if (xen_hvm_domain() && (xen_platform_pci_unplug & state))
		return true;

	return xen_has_pv_devices();
}