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
struct mount {int vfs_flag; } ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  MNTOPT_NOSETUID ; 
 int /*<<< orphan*/  MNTOPT_SETUID ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int MNT_USER ; 
 int /*<<< orphan*/  PRIV_VFS_MOUNT_NONUSER ; 
 int VFS_NOSETUID ; 
 scalar_t__ priv_check_cred (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_clearmntopt (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_setmntopt (struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
secpolicy_fs_mount_clearopts(cred_t *cr, struct mount *vfsp)
{

	if (priv_check_cred(cr, PRIV_VFS_MOUNT_NONUSER) != 0) {
		MNT_ILOCK(vfsp);
		vfsp->vfs_flag |= VFS_NOSETUID | MNT_USER;
		vfs_clearmntopt(vfsp, MNTOPT_SETUID);
		vfs_setmntopt(vfsp, MNTOPT_NOSETUID, NULL, 0);
		MNT_IUNLOCK(vfsp);
	}
}