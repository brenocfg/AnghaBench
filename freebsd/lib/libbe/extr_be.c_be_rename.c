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
struct renameflags {int nounmount; } ;
struct TYPE_6__ {int /*<<< orphan*/  lzh; } ;
typedef  TYPE_1__ libbe_handle_t ;

/* Variables and functions */
 int BE_ERR_EXISTS ; 
 int BE_ERR_NOENT ; 
 int BE_ERR_UNKNOWN ; 
 int BE_ERR_ZFSOPEN ; 
 int BE_MAXPATHLEN ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int be_root_concat (TYPE_1__*,char const*,char*) ; 
 int be_validate_name (TYPE_1__*,char const*) ; 
 int set_error (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_dataset_exists (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int zfs_rename (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,struct renameflags) ; 

int
be_rename(libbe_handle_t *lbh, const char *old, const char *new)
{
	char full_old[BE_MAXPATHLEN];
	char full_new[BE_MAXPATHLEN];
	zfs_handle_t *zfs_hdl;
	int err;

	/*
	 * be_validate_name is documented not to set error state, so we should
	 * do so here.
	 */
	if ((err = be_validate_name(lbh, new)) != 0)
		return (set_error(lbh, err));
	if ((err = be_root_concat(lbh, old, full_old)) != 0)
		return (set_error(lbh, err));
	if ((err = be_root_concat(lbh, new, full_new)) != 0)
		return (set_error(lbh, err));

	if (!zfs_dataset_exists(lbh->lzh, full_old, ZFS_TYPE_DATASET))
		return (set_error(lbh, BE_ERR_NOENT));

	if (zfs_dataset_exists(lbh->lzh, full_new, ZFS_TYPE_DATASET))
		return (set_error(lbh, BE_ERR_EXISTS));

	if ((zfs_hdl = zfs_open(lbh->lzh, full_old,
	    ZFS_TYPE_FILESYSTEM)) == NULL)
		return (set_error(lbh, BE_ERR_ZFSOPEN));

	/* recurse, nounmount, forceunmount */
	struct renameflags flags = {
		.nounmount = 1,
	};

	err = zfs_rename(zfs_hdl, NULL, full_new, flags);

	zfs_close(zfs_hdl);
	if (err != 0)
		return (set_error(lbh, BE_ERR_UNKNOWN));
	return (0);
}