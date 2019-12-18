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
struct pcd_unit {int changed; } ;
struct cdrom_device_info {struct pcd_unit* handle; } ;

/* Variables and functions */
 unsigned int DISK_EVENT_MEDIA_CHANGE ; 

__attribute__((used)) static unsigned int pcd_check_events(struct cdrom_device_info *cdi,
				     unsigned int clearing, int slot_nr)
{
	struct pcd_unit *cd = cdi->handle;
	int res = cd->changed;
	if (res)
		cd->changed = 0;
	return res ? DISK_EVENT_MEDIA_CHANGE : 0;
}