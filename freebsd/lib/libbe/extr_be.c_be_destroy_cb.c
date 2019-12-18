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
struct be_destroy_data {char* snapname; TYPE_1__* lbh; } ;
typedef  int /*<<< orphan*/  path ;
struct TYPE_2__ {int /*<<< orphan*/  lzh; } ;

/* Variables and functions */
 int BE_MAXPATHLEN ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  zfs_dataset_exists (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int zfs_destroy (int /*<<< orphan*/ *,int) ; 
 char* zfs_get_name (int /*<<< orphan*/ *) ; 
 int zfs_iter_children (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),void*) ; 
 int zfs_iter_filesystems (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),void*) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
be_destroy_cb(zfs_handle_t *zfs_hdl, void *data)
{
	char path[BE_MAXPATHLEN];
	struct be_destroy_data *bdd;
	zfs_handle_t *snap;
	int err;

	bdd = (struct be_destroy_data *)data;
	if (bdd->snapname == NULL) {
		err = zfs_iter_children(zfs_hdl, be_destroy_cb, data);
		if (err != 0)
			return (err);
		return (zfs_destroy(zfs_hdl, false));
	}
	/* If we're dealing with snapshots instead, delete that one alone */
	err = zfs_iter_filesystems(zfs_hdl, be_destroy_cb, data);
	if (err != 0)
		return (err);
	/*
	 * This part is intentionally glossing over any potential errors,
	 * because there's a lot less potential for errors when we're cleaning
	 * up snapshots rather than a full deep BE.  The primary error case
	 * here being if the snapshot doesn't exist in the first place, which
	 * the caller will likely deem insignificant as long as it doesn't
	 * exist after the call.  Thus, such a missing snapshot shouldn't jam
	 * up the destruction.
	 */
	snprintf(path, sizeof(path), "%s@%s", zfs_get_name(zfs_hdl),
	    bdd->snapname);
	if (!zfs_dataset_exists(bdd->lbh->lzh, path, ZFS_TYPE_SNAPSHOT))
		return (0);
	snap = zfs_open(bdd->lbh->lzh, path, ZFS_TYPE_SNAPSHOT);
	if (snap != NULL)
		zfs_destroy(snap, false);
	return (0);
}