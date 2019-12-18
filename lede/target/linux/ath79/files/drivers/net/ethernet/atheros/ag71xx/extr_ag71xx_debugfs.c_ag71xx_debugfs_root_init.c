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
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 scalar_t__ ag71xx_debugfs_root ; 
 scalar_t__ debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ag71xx_debugfs_root_init(void)
{
	if (ag71xx_debugfs_root)
		return -EBUSY;

	ag71xx_debugfs_root = debugfs_create_dir(KBUILD_MODNAME, NULL);
	if (!ag71xx_debugfs_root)
		return -ENOENT;

	return 0;
}