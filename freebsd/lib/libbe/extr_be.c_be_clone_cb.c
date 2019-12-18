#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct libbe_deep_clone {char* snapname; int depth_limit; int depth; TYPE_1__* lbh; } ;
struct libbe_dccb {int /*<<< orphan*/ * props; int /*<<< orphan*/ * zhp; TYPE_1__* lbh; } ;
typedef  int /*<<< orphan*/  snap_path ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  be_path ;
struct TYPE_2__ {int /*<<< orphan*/  lzh; } ;

/* Variables and functions */
 int BE_ERR_EXISTS ; 
 scalar_t__ BE_ERR_SUCCESS ; 
 int BE_ERR_UNKNOWN ; 
 int BE_ERR_ZFSCLONE ; 
 int BE_ERR_ZFSOPEN ; 
 int BE_MAXPATHLEN ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 scalar_t__ ZPROP_INVAL ; 
 int /*<<< orphan*/  be_deep_clone_prop ; 
 scalar_t__ be_get_path (struct libbe_deep_clone*,char const*,char*,int) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int set_error (TYPE_1__*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 int zfs_clone (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_dataset_exists (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* zfs_get_name (int /*<<< orphan*/ *) ; 
 int zfs_iter_filesystems (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),struct libbe_deep_clone*) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zprop_iter (int /*<<< orphan*/ ,struct libbe_dccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
be_clone_cb(zfs_handle_t *ds, void *data)
{
	int err;
	char be_path[BE_MAXPATHLEN];
	char snap_path[BE_MAXPATHLEN];
	const char *dspath;
	zfs_handle_t *snap_hdl;
	nvlist_t *props;
	struct libbe_deep_clone *ldc;
	struct libbe_dccb dccb;

	ldc = (struct libbe_deep_clone *)data;
	dspath = zfs_get_name(ds);

	snprintf(snap_path, sizeof(snap_path), "%s@%s", dspath, ldc->snapname);

	/* construct the boot environment path from the dataset we're cloning */
	if (be_get_path(ldc, dspath, be_path, sizeof(be_path)) != BE_ERR_SUCCESS)
		return (set_error(ldc->lbh, BE_ERR_UNKNOWN));

	/* the dataset to be created (i.e. the boot environment) already exists */
	if (zfs_dataset_exists(ldc->lbh->lzh, be_path, ZFS_TYPE_DATASET))
		return (set_error(ldc->lbh, BE_ERR_EXISTS));

	/* no snapshot found for this dataset, silently skip it */
	if (!zfs_dataset_exists(ldc->lbh->lzh, snap_path, ZFS_TYPE_SNAPSHOT))
		return (0);

	if ((snap_hdl =
	    zfs_open(ldc->lbh->lzh, snap_path, ZFS_TYPE_SNAPSHOT)) == NULL)
		return (set_error(ldc->lbh, BE_ERR_ZFSOPEN));

	nvlist_alloc(&props, NV_UNIQUE_NAME, KM_SLEEP);
	nvlist_add_string(props, "canmount", "noauto");

	dccb.lbh = ldc->lbh;
	dccb.zhp = ds;
	dccb.props = props;
	if (zprop_iter(be_deep_clone_prop, &dccb, B_FALSE, B_FALSE,
	    ZFS_TYPE_FILESYSTEM) == ZPROP_INVAL)
		return (-1);

	if ((err = zfs_clone(snap_hdl, be_path, props)) != 0)
		return (set_error(ldc->lbh, BE_ERR_ZFSCLONE));

	nvlist_free(props);
	zfs_close(snap_hdl);

	if (ldc->depth_limit == -1 || ldc->depth < ldc->depth_limit) {
		ldc->depth++;
		err = zfs_iter_filesystems(ds, be_clone_cb, ldc);
		ldc->depth--;
	}

	return (set_error(ldc->lbh, err));
}