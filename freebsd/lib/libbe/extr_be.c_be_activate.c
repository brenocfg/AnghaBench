#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_9__ {int /*<<< orphan*/  lzh; int /*<<< orphan*/  active_phandle; int /*<<< orphan*/  bootfs; } ;
typedef  TYPE_1__ libbe_handle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BE_ERR_NOPOOL ; 
 int BE_ERR_SUCCESS ; 
 int BE_ERR_UNKNOWN ; 
 int BE_MAXPATHLEN ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 scalar_t__ be_deactivate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int be_exists (TYPE_1__*,char*) ; 
 scalar_t__ be_get_dataset_props (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ be_prop_list_alloc (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  be_root_concat (TYPE_1__*,char const*,char*) ; 
 int be_set_nextboot (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int set_error (TYPE_1__*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int zfs_promote (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zpool_set_prop (int /*<<< orphan*/ ,char*,char*) ; 

int
be_activate(libbe_handle_t *lbh, const char *bootenv, bool temporary)
{
	char be_path[BE_MAXPATHLEN];
	char buf[BE_MAXPATHLEN];
	nvlist_t *config, *dsprops, *vdevs;
	char *origin;
	uint64_t pool_guid;
	zfs_handle_t *zhp;
	int err;

	be_root_concat(lbh, bootenv, be_path);

	/* Note: be_exists fails if mountpoint is not / */
	if ((err = be_exists(lbh, be_path)) != 0)
		return (set_error(lbh, err));

	if (temporary) {
		config = zpool_get_config(lbh->active_phandle, NULL);
		if (config == NULL)
			/* config should be fetchable... */
			return (set_error(lbh, BE_ERR_UNKNOWN));

		if (nvlist_lookup_uint64(config, ZPOOL_CONFIG_POOL_GUID,
		    &pool_guid) != 0)
			/* Similarly, it shouldn't be possible */
			return (set_error(lbh, BE_ERR_UNKNOWN));

		/* Expected format according to zfsbootcfg(8) man */
		snprintf(buf, sizeof(buf), "zfs:%s:", be_path);

		/* We have no config tree */
		if (nvlist_lookup_nvlist(config, ZPOOL_CONFIG_VDEV_TREE,
		    &vdevs) != 0)
			return (set_error(lbh, BE_ERR_NOPOOL));

		return (be_set_nextboot(lbh, vdevs, pool_guid, buf));
	} else {
		if (be_deactivate(lbh, lbh->bootfs) != 0)
			return (-1);

		/* Obtain bootenv zpool */
		err = zpool_set_prop(lbh->active_phandle, "bootfs", be_path);
		if (err)
			return (-1);

		zhp = zfs_open(lbh->lzh, be_path, ZFS_TYPE_FILESYSTEM);
		if (zhp == NULL)
			return (-1);

		if (be_prop_list_alloc(&dsprops) != 0)
			return (-1);

		if (be_get_dataset_props(lbh, be_path, dsprops) != 0) {
			nvlist_free(dsprops);
			return (-1);
		}

		if (nvlist_lookup_string(dsprops, "origin", &origin) == 0)
			err = zfs_promote(zhp);
		nvlist_free(dsprops);

		zfs_close(zhp);

		if (err)
			return (-1);
	}

	return (BE_ERR_SUCCESS);
}