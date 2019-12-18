#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct be_mount_info {char* be; char* mountpoint; int mntflags; int deepmount; scalar_t__ depth; TYPE_1__* lbh; } ;
typedef  int /*<<< orphan*/  mnt_temp ;
struct TYPE_6__ {int /*<<< orphan*/  lzh; } ;
typedef  TYPE_1__ libbe_handle_t ;

/* Variables and functions */
 int BE_ERR_IO ; 
 int BE_ERR_MOUNTED ; 
 int BE_ERR_SUCCESS ; 
 int BE_ERR_ZFSOPEN ; 
 int BE_MAXPATHLEN ; 
 int BE_MNT_DEEP ; 
 int BE_MNT_FORCE ; 
 int MNT_FORCE ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int be_exists (TYPE_1__*,char*) ; 
 scalar_t__ be_mount_iter (int /*<<< orphan*/ *,struct be_mount_info*) ; 
 int be_root_concat (TYPE_1__*,char*,char*) ; 
 scalar_t__ is_mounted (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mkdtemp (char*) ; 
 int set_error (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
be_mount(libbe_handle_t *lbh, char *bootenv, char *mountpoint, int flags,
    char *result_loc)
{
	char be[BE_MAXPATHLEN];
	char mnt_temp[BE_MAXPATHLEN];
	int mntflags, mntdeep;
	int err;
	struct be_mount_info info;
	zfs_handle_t *zhdl;

	if ((err = be_root_concat(lbh, bootenv, be)) != 0)
		return (set_error(lbh, err));

	if ((err = be_exists(lbh, bootenv)) != 0)
		return (set_error(lbh, err));

	if (is_mounted(lbh->lzh, be, NULL))
		return (set_error(lbh, BE_ERR_MOUNTED));

	mntdeep = (flags & BE_MNT_DEEP) ? 1 : 0;
	mntflags = (flags & BE_MNT_FORCE) ? MNT_FORCE : 0;

	/* Create mountpoint if it is not specified */
	if (mountpoint == NULL) {
		strlcpy(mnt_temp, "/tmp/be_mount.XXXX", sizeof(mnt_temp));
		if (mkdtemp(mnt_temp) == NULL)
			return (set_error(lbh, BE_ERR_IO));
	}

	if ((zhdl = zfs_open(lbh->lzh, be, ZFS_TYPE_FILESYSTEM)) == NULL)
		return (set_error(lbh, BE_ERR_ZFSOPEN));

	info.lbh = lbh;
	info.be = be;
	info.mountpoint = (mountpoint == NULL) ? mnt_temp : mountpoint;
	info.mntflags = mntflags;
	info.deepmount = mntdeep;
	info.depth = 0;

	if((err = be_mount_iter(zhdl, &info) != 0)) {
		zfs_close(zhdl);
		return (err);
	}
	zfs_close(zhdl);

	if (result_loc != NULL)
		strlcpy(result_loc, mountpoint == NULL ? mnt_temp : mountpoint,
		    BE_MAXPATHLEN);

	return (BE_ERR_SUCCESS);
}