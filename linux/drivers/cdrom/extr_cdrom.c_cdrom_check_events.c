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
struct cdrom_device_info {unsigned int vfs_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdrom_update_events (struct cdrom_device_info*,unsigned int) ; 

unsigned int cdrom_check_events(struct cdrom_device_info *cdi,
				unsigned int clearing)
{
	unsigned int events;

	cdrom_update_events(cdi, clearing);
	events = cdi->vfs_events;
	cdi->vfs_events = 0;
	return events;
}