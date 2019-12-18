#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct statfs {int dummy; } ;
struct extmnttab {int /*<<< orphan*/  mnt_fstype; } ;
struct TYPE_3__ {int /*<<< orphan*/  rootfs; int /*<<< orphan*/  lzh; } ;
typedef  TYPE_1__ libbe_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MNTTYPE_ZFS ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 scalar_t__ statfs (char*,struct statfs*) ; 
 int /*<<< orphan*/  statfs2mnttab (struct statfs*,struct extmnttab*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_path_to_zhandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
be_locate_rootfs(libbe_handle_t *lbh)
{
	struct statfs sfs;
	struct extmnttab entry;
	zfs_handle_t *zfs;

	/*
	 * Check first if root is ZFS; if not, we'll bail on rootfs capture.
	 * Unfortunately needed because zfs_path_to_zhandle will emit to
	 * stderr if / isn't actually a ZFS filesystem, which we'd like
	 * to avoid.
	 */
	if (statfs("/", &sfs) == 0) {
		statfs2mnttab(&sfs, &entry);
		if (strcmp(entry.mnt_fstype, MNTTYPE_ZFS) != 0)
			return (1);
	} else
		return (1);
	zfs = zfs_path_to_zhandle(lbh->lzh, "/", ZFS_TYPE_FILESYSTEM);
	if (zfs == NULL)
		return (1);

	strlcpy(lbh->rootfs, zfs_get_name(zfs), sizeof(lbh->rootfs));
	zfs_close(zfs);
	return (0);
}