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
 int XEN_UNPLUG_UNNECESSARY ; 
 int /*<<< orphan*/  xen_domain () ; 
 int xen_platform_pci_unplug ; 
 scalar_t__ xen_pv_domain () ; 

bool xen_has_pv_and_legacy_disk_devices(void)
{
	if (!xen_domain())
		return false;

	/* N.B. This is only ever used in HVM mode */
	if (xen_pv_domain())
		return false;

	if (xen_platform_pci_unplug & XEN_UNPLUG_UNNECESSARY)
		return true;

	return false;
}