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
 int /*<<< orphan*/  drbd_debugfs_minors ; 
 int /*<<< orphan*/  drbd_debugfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbd_debugfs_resources ; 
 int /*<<< orphan*/  drbd_debugfs_root ; 
 int /*<<< orphan*/  drbd_debugfs_version ; 

void drbd_debugfs_cleanup(void)
{
	drbd_debugfs_remove(&drbd_debugfs_resources);
	drbd_debugfs_remove(&drbd_debugfs_minors);
	drbd_debugfs_remove(&drbd_debugfs_version);
	drbd_debugfs_remove(&drbd_debugfs_root);
}