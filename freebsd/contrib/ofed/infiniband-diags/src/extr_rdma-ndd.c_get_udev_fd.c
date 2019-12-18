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
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  mon ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udev ; 
 int /*<<< orphan*/  udev_monitor_enable_receiving (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_monitor_filter_add_match_subsystem_devtype (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int udev_monitor_get_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_monitor_new_from_netlink (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int get_udev_fd(void)
{
	mon = udev_monitor_new_from_netlink(udev, "udev");
	if (!mon) {
		syslog(LOG_ERR, "udev monitoring failed\n");
		return -1;
	}

	udev_monitor_filter_add_match_subsystem_devtype(mon, "infiniband", NULL);
	udev_monitor_enable_receiving(mon);
	return udev_monitor_get_fd(mon);
}