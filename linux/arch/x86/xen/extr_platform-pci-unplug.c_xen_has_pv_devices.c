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
 int XEN_UNPLUG_ALL ; 
 int XEN_UNPLUG_NEVER ; 
 int XEN_UNPLUG_UNNECESSARY ; 
 int /*<<< orphan*/  xen_domain () ; 
 int xen_platform_pci_unplug ; 
 scalar_t__ xen_pv_domain () ; 
 scalar_t__ xen_pvh_domain () ; 

bool xen_has_pv_devices(void)
{
	if (!xen_domain())
		return false;

	/* PV and PVH domains always have them. */
	if (xen_pv_domain() || xen_pvh_domain())
		return true;

	/* And user has xen_platform_pci=0 set in guest config as
	 * driver did not modify the value. */
	if (xen_platform_pci_unplug == 0)
		return false;

	if (xen_platform_pci_unplug & XEN_UNPLUG_NEVER)
		return false;

	if (xen_platform_pci_unplug & XEN_UNPLUG_ALL)
		return true;

	/* This is an odd one - we are going to run legacy
	 * and PV drivers at the same time. */
	if (xen_platform_pci_unplug & XEN_UNPLUG_UNNECESSARY)
		return true;

	/* And the caller has to follow with xen_pv_{disk,nic}_devices
	 * to be certain which driver can load. */
	return false;
}