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
 int /*<<< orphan*/  taskq_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_vnodes_adjust_back () ; 
 int /*<<< orphan*/  zfs_znode_fini () ; 
 int /*<<< orphan*/  zfsctl_fini () ; 
 int /*<<< orphan*/  zfsvfs_taskq ; 

void
zfs_fini(void)
{
#if defined(__FreeBSD__)
	taskq_destroy(zfsvfs_taskq);
#endif
	zfsctl_fini();
	zfs_znode_fini();
	zfs_vnodes_adjust_back();
}