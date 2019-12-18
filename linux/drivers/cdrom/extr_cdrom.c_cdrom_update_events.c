#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cdrom_device_info {unsigned int vfs_events; unsigned int ioctl_events; TYPE_1__* ops; } ;
struct TYPE_2__ {unsigned int (* check_events ) (struct cdrom_device_info*,unsigned int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CDSL_CURRENT ; 
 unsigned int stub1 (struct cdrom_device_info*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdrom_update_events(struct cdrom_device_info *cdi,
				unsigned int clearing)
{
	unsigned int events;

	events = cdi->ops->check_events(cdi, clearing, CDSL_CURRENT);
	cdi->vfs_events |= events;
	cdi->ioctl_events |= events;
}