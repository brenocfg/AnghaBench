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
 int /*<<< orphan*/  GID_OPERATOR ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  ZFS_DEV_NAME ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_cdevsw ; 
 int /*<<< orphan*/  zfsdev ; 

__attribute__((used)) static void
zfsdev_init(void)
{
	zfsdev = make_dev(&zfs_cdevsw, 0x0, UID_ROOT, GID_OPERATOR, 0666,
	    ZFS_DEV_NAME);
}