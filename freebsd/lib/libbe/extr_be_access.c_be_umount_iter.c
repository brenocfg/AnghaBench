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
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct be_mount_info {int /*<<< orphan*/  lbh; int /*<<< orphan*/  mntflags; int /*<<< orphan*/  depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_ERR_BADPATH ; 
 int /*<<< orphan*/  BE_ERR_PATHBUSY ; 
 int /*<<< orphan*/  BE_ERR_PATHLEN ; 
 int /*<<< orphan*/  BE_ERR_PERMS ; 
 int /*<<< orphan*/  BE_ERR_UNKNOWN ; 
#define  EBUSY 133 
#define  ELOOP 132 
#define  ENAMETOOLONG 131 
#define  ENOENT 130 
#define  ENOTDIR 129 
#define  EPERM 128 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_is_mounted (int /*<<< orphan*/ *,char**) ; 
 int zfs_iter_filesystems (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),struct be_mount_info*) ; 
 scalar_t__ zfs_unmount (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
be_umount_iter(zfs_handle_t *zfs_hdl, void *data)
{

	int err;
	char *mountpoint;
	struct be_mount_info *info;

	info = (struct be_mount_info *)data;

	++info->depth;
	if((err = zfs_iter_filesystems(zfs_hdl, be_umount_iter, info)) != 0) {
		return (err);
	}
	--info->depth;

	if (!zfs_is_mounted(zfs_hdl, &mountpoint)) {
		return (0);
	}
	free(mountpoint);

	if (zfs_unmount(zfs_hdl, NULL, info->mntflags) != 0) {
		switch (errno) {
		case ENAMETOOLONG:
			return (set_error(info->lbh, BE_ERR_PATHLEN));
		case ELOOP:
		case ENOENT:
		case ENOTDIR:
			return (set_error(info->lbh, BE_ERR_BADPATH));
		case EPERM:
			return (set_error(info->lbh, BE_ERR_PERMS));
		case EBUSY:
			return (set_error(info->lbh, BE_ERR_PATHBUSY));
		default:
			return (set_error(info->lbh, BE_ERR_UNKNOWN));
		}
	}
	return (0);
}