#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct be_mountcheck_info {char const* path; int /*<<< orphan*/ * name; } ;
struct TYPE_5__ {int single_object; int /*<<< orphan*/ * list; TYPE_2__* lbh; } ;
typedef  TYPE_1__ prop_data_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_6__ {int /*<<< orphan*/  root; int /*<<< orphan*/  lzh; } ;
typedef  TYPE_2__ libbe_handle_t ;

/* Variables and functions */
 int BE_ERR_ZFSOPEN ; 
 int BE_MAXPATHLEN ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  be_mountcheck_cb ; 
 int /*<<< orphan*/  bzero (char**,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prop_list_builder_cb (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_iter_filesystems (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct be_mountcheck_info*) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
be_mounted_at(libbe_handle_t *lbh, const char *path, nvlist_t *details)
{
	char be[BE_MAXPATHLEN];
	zfs_handle_t *root_hdl;
	struct be_mountcheck_info info;
	prop_data_t propinfo;

	bzero(&be, BE_MAXPATHLEN);
	if ((root_hdl = zfs_open(lbh->lzh, lbh->root,
	    ZFS_TYPE_FILESYSTEM)) == NULL)
		return (BE_ERR_ZFSOPEN);

	info.path = path;
	info.name = NULL;
	zfs_iter_filesystems(root_hdl, be_mountcheck_cb, &info);
	zfs_close(root_hdl);

	if (info.name != NULL) {
		if (details != NULL) {
			if ((root_hdl = zfs_open(lbh->lzh, lbh->root,
			    ZFS_TYPE_FILESYSTEM)) == NULL) {
				free(info.name);
				return (BE_ERR_ZFSOPEN);
			}

			propinfo.lbh = lbh;
			propinfo.list = details;
			propinfo.single_object = false;
			prop_list_builder_cb(root_hdl, &propinfo);
			zfs_close(root_hdl);
		}
		free(info.name);
		return (0);
	}
	return (1);
}