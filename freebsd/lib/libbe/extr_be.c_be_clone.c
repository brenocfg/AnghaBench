#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct libbe_deep_clone {char const* bename; char* snapname; int depth_limit; scalar_t__ depth; TYPE_1__* lbh; } ;
struct TYPE_7__ {int /*<<< orphan*/  lzh; } ;
typedef  TYPE_1__ libbe_handle_t ;

/* Variables and functions */
 int BE_ERR_UNKNOWN ; 
 int BE_MAXPATHLEN ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int be_clone_cb (int /*<<< orphan*/ *,struct libbe_deep_clone*) ; 
 int be_root_concat (TYPE_1__*,char const*,char*) ; 
 int be_validate_name (TYPE_1__*,char const*) ; 
 int be_validate_snap (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int set_error (TYPE_1__*,int) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
be_clone(libbe_handle_t *lbh, const char *bename, const char *snapshot, int depth)
{
	int err;
	char snap_path[BE_MAXPATHLEN];
	char *parentname, *snapname;
	zfs_handle_t *parent_hdl;
	struct libbe_deep_clone ldc;

        /* ensure the boot environment name is valid */
	if ((err = be_validate_name(lbh, bename)) != 0)
		return (set_error(lbh, err));

	/*
	 * prepend the boot environment root path if we're
	 * given a partial snapshot name.
	 */
	if ((err = be_root_concat(lbh, snapshot, snap_path)) != 0)
		return (set_error(lbh, err));

	/* ensure the snapshot exists */
	if ((err = be_validate_snap(lbh, snap_path)) != 0)
		return (set_error(lbh, err));

        /* get a copy of the snapshot path so we can disect it */
	if ((parentname = strdup(snap_path)) == NULL)
		return (set_error(lbh, BE_ERR_UNKNOWN));

        /* split dataset name from snapshot name */
	snapname = strchr(parentname, '@');
	if (snapname == NULL) {
		free(parentname);
		return (set_error(lbh, BE_ERR_UNKNOWN));
	}
	*snapname = '\0';
	snapname++;

        /* set-up the boot environment */
        ldc.lbh = lbh;
        ldc.bename = bename;
        ldc.snapname = snapname;
	ldc.depth = 0;
	ldc.depth_limit = depth;

        /* the boot environment will be cloned from this dataset */
	parent_hdl = zfs_open(lbh->lzh, parentname, ZFS_TYPE_DATASET);

        /* create the boot environment */
	err = be_clone_cb(parent_hdl, &ldc);

	free(parentname);
	return (set_error(lbh, err));
}