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
 int /*<<< orphan*/  LOG_INFO ; 
 char* sys_dir ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udev ; 
 scalar_t__ udev_get_sys_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_log_fn ; 
 int /*<<< orphan*/  udev_new () ; 
 int /*<<< orphan*/  udev_set_log_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_set_log_priority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_udev(void)
{
	udev = udev_new();
	if (!udev) {
		syslog(LOG_ERR, "udev_new failed\n");
		return;
	}

	udev_set_log_fn(udev, udev_log_fn);
	udev_set_log_priority(udev, LOG_INFO);
#if HAVE_UDEV_GET_SYS_PATH
	sys_dir = (char *)udev_get_sys_path(udev);
#endif
}