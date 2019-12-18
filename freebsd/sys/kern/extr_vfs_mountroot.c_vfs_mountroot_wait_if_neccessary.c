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
 int ENODEV ; 
 int /*<<< orphan*/  g_waitidle () ; 
 int hz ; 
 scalar_t__ parse_mount_dev_present (char const*) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ root_mount_always_wait ; 
 int root_mount_timeout ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 
 int /*<<< orphan*/  vfs_mountroot_wait () ; 

__attribute__((used)) static int
vfs_mountroot_wait_if_neccessary(const char *fs, const char *dev)
{
	int delay, timeout;

	/*
	 * In case of ZFS and NFS we don't have a way to wait for
	 * specific device.  Also do the wait if the user forced that
	 * behaviour by setting vfs.root_mount_always_wait=1.
	 */
	if (strcmp(fs, "zfs") == 0 || strstr(fs, "nfs") != NULL ||
	    dev[0] == '\0' || root_mount_always_wait != 0) {
		vfs_mountroot_wait();
		return (0);
	}

	/*
	 * Otherwise, no point in waiting if the device is already there.
	 * Note that we must wait for GEOM to finish reconfiguring itself,
	 * eg for geom_part(4) to finish tasting.
	 */
	g_waitidle();
	if (parse_mount_dev_present(dev))
		return (0);

	/*
	 * No luck.  Let's wait.  This code looks weird, but it's that way
	 * to behave exactly as it used to work before.
	 */
	vfs_mountroot_wait();
	printf("mountroot: waiting for device %s...\n", dev);
	delay = hz / 10;
	timeout = root_mount_timeout * hz;
	do {
		pause("rmdev", delay);
		timeout -= delay;
	} while (timeout > 0 && !parse_mount_dev_present(dev));

	if (timeout <= 0)
		return (ENODEV);

	return (0);
}