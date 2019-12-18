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
struct TYPE_2__ {int /*<<< orphan*/ * list; scalar_t__ single_object; int /*<<< orphan*/ * lbh; } ;
typedef  TYPE_1__ prop_data_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libbe_handle_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  ZFS_PROP_CREATION ; 
 int /*<<< orphan*/  ZFS_PROP_MOUNTPOINT ; 
 int /*<<< orphan*/  ZFS_PROP_ORIGIN ; 
 int /*<<< orphan*/  ZFS_PROP_REFERENCED ; 
 int /*<<< orphan*/  ZFS_PROP_USED ; 
 int /*<<< orphan*/  ZFS_PROP_USEDDS ; 
 int /*<<< orphan*/  ZFS_PROP_USEDREFRESERV ; 
 int /*<<< orphan*/  ZFS_PROP_USEDSNAP ; 
 int /*<<< orphan*/  be_active_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be_nextboot_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_add_boolean_value (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  nvlist_add_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 char* strrchr (char const*,char) ; 
 char* zfs_get_name (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_is_mounted (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ zfs_prop_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
prop_list_builder_cb(zfs_handle_t *zfs_hdl, void *data_p)
{
	char buf[512], *mountpoint;
	prop_data_t *data;
	libbe_handle_t *lbh;
	nvlist_t *props;
	const char *dataset, *name;
	boolean_t mounted;

	/*
	 * XXX TODO:
	 *      some system for defining constants for the nvlist keys
	 *      error checking
	 */
	data = (prop_data_t *)data_p;
	lbh = data->lbh;

	if (data->single_object)
		props = data->list;
	else
		nvlist_alloc(&props, NV_UNIQUE_NAME, KM_SLEEP);

	dataset = zfs_get_name(zfs_hdl);
	nvlist_add_string(props, "dataset", dataset);

	name = strrchr(dataset, '/') + 1;
	nvlist_add_string(props, "name", name);

	mounted = zfs_is_mounted(zfs_hdl, &mountpoint);

	if (mounted)
		nvlist_add_string(props, "mounted", mountpoint);

	if (zfs_prop_get(zfs_hdl, ZFS_PROP_MOUNTPOINT, buf, 512,
	    NULL, NULL, 0, 1) == 0)
		nvlist_add_string(props, "mountpoint", buf);

	if (zfs_prop_get(zfs_hdl, ZFS_PROP_ORIGIN, buf, 512,
	    NULL, NULL, 0, 1) == 0)
		nvlist_add_string(props, "origin", buf);

	if (zfs_prop_get(zfs_hdl, ZFS_PROP_CREATION, buf, 512,
	    NULL, NULL, 0, 1) == 0)
		nvlist_add_string(props, "creation", buf);

	nvlist_add_boolean_value(props, "active",
	    (strcmp(be_active_path(lbh), dataset) == 0));

	if (zfs_prop_get(zfs_hdl, ZFS_PROP_USED, buf, 512,
	    NULL, NULL, 0, 1) == 0)
		nvlist_add_string(props, "used", buf);

	if (zfs_prop_get(zfs_hdl, ZFS_PROP_USEDDS, buf, 512,
	    NULL, NULL, 0, 1) == 0)
		nvlist_add_string(props, "usedds", buf);

	if (zfs_prop_get(zfs_hdl, ZFS_PROP_USEDSNAP, buf, 512,
	    NULL, NULL, 0, 1) == 0)
		nvlist_add_string(props, "usedsnap", buf);

	if (zfs_prop_get(zfs_hdl, ZFS_PROP_USEDREFRESERV, buf, 512,
	    NULL, NULL, 0, 1) == 0)
		nvlist_add_string(props, "usedrefreserv", buf);

	if (zfs_prop_get(zfs_hdl, ZFS_PROP_REFERENCED, buf, 512,
	    NULL, NULL, 0, 1) == 0)
		nvlist_add_string(props, "referenced", buf);

	nvlist_add_boolean_value(props, "nextboot",
	    (strcmp(be_nextboot_path(lbh), dataset) == 0));

	if (!data->single_object)
		nvlist_add_nvlist(data->list, name, props);

	return (0);
}