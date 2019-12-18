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
struct nitrox_device {struct dentry* debugfs_dir; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct nitrox_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_fops ; 
 int /*<<< orphan*/  firmware_fops ; 
 int /*<<< orphan*/  stats_fops ; 

void nitrox_debugfs_init(struct nitrox_device *ndev)
{
	struct dentry *dir;

	dir = debugfs_create_dir(KBUILD_MODNAME, NULL);

	ndev->debugfs_dir = dir;
	debugfs_create_file("firmware", 0400, dir, ndev, &firmware_fops);
	debugfs_create_file("device", 0400, dir, ndev, &device_fops);
	debugfs_create_file("stats", 0400, dir, ndev, &stats_fops);
}