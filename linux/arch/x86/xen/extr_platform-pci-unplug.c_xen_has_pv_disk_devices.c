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
 int XEN_UNPLUG_ALL_IDE_DISKS ; 
 int XEN_UNPLUG_AUX_IDE_DISKS ; 
 int __xen_has_pv_device (int) ; 

bool xen_has_pv_disk_devices(void)
{
	return __xen_has_pv_device(XEN_UNPLUG_ALL_IDE_DISKS |
				   XEN_UNPLUG_AUX_IDE_DISKS | XEN_UNPLUG_ALL);
}