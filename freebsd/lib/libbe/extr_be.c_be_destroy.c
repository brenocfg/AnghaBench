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
struct be_destroy_data {int /*<<< orphan*/ * snapname; TYPE_1__* lbh; } ;
typedef  int /*<<< orphan*/  origin ;
struct TYPE_6__ {char* root; int /*<<< orphan*/  lzh; int /*<<< orphan*/  bootfs; int /*<<< orphan*/  rootfs; } ;
typedef  TYPE_1__ libbe_handle_t ;

/* Variables and functions */
 int BE_DESTROY_AUTOORIGIN ; 
 int BE_DESTROY_FORCE ; 
 int BE_DESTROY_ORIGIN ; 
 int BE_DESTROY_WANTORIGIN ; 
 int /*<<< orphan*/  BE_ERR_DESTROYACT ; 
 int /*<<< orphan*/  BE_ERR_DESTROYMNT ; 
 int /*<<< orphan*/  BE_ERR_INVORIGIN ; 
 int /*<<< orphan*/  BE_ERR_NOENT ; 
 int /*<<< orphan*/  BE_ERR_NOMEM ; 
 int /*<<< orphan*/  BE_ERR_NOORIGIN ; 
 int /*<<< orphan*/  BE_ERR_UNKNOWN ; 
 int /*<<< orphan*/  BE_ERR_ZFSOPEN ; 
 int BE_MAXPATHLEN ; 
 int EBUSY ; 
 int /*<<< orphan*/  ZFS_PROP_ORIGIN ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 int be_destroy_cb (int /*<<< orphan*/ *,struct be_destroy_data*) ; 
 scalar_t__ be_is_auto_snapshot_name (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  be_root_concat (TYPE_1__*,char const*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int set_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dataset_exists (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int zfs_is_mounted (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_unmount (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
be_destroy(libbe_handle_t *lbh, const char *name, int options)
{
	struct be_destroy_data bdd;
	char origin[BE_MAXPATHLEN], path[BE_MAXPATHLEN];
	zfs_handle_t *fs;
	char *snapdelim;
	int err, force, mounted;
	size_t rootlen;

	bdd.lbh = lbh;
	bdd.snapname = NULL;
	force = options & BE_DESTROY_FORCE;
	*origin = '\0';

	be_root_concat(lbh, name, path);

	if ((snapdelim = strchr(path, '@')) == NULL) {
		if (!zfs_dataset_exists(lbh->lzh, path, ZFS_TYPE_FILESYSTEM))
			return (set_error(lbh, BE_ERR_NOENT));

		if (strcmp(path, lbh->rootfs) == 0 ||
		    strcmp(path, lbh->bootfs) == 0)
			return (set_error(lbh, BE_ERR_DESTROYACT));

		fs = zfs_open(lbh->lzh, path, ZFS_TYPE_FILESYSTEM);
		if (fs == NULL)
			return (set_error(lbh, BE_ERR_ZFSOPEN));

		if ((options & BE_DESTROY_WANTORIGIN) != 0 &&
		    zfs_prop_get(fs, ZFS_PROP_ORIGIN, origin, sizeof(origin),
		    NULL, NULL, 0, 1) != 0 &&
		    (options & BE_DESTROY_ORIGIN) != 0)
			return (set_error(lbh, BE_ERR_NOORIGIN));

		/*
		 * If the caller wants auto-origin destruction and the origin
		 * name matches one of our automatically created snapshot names
		 * (i.e. strftime("%F-%T") with a serial at the end), then
		 * we'll set the DESTROY_ORIGIN flag and nuke it
		 * be_is_auto_snapshot_name is exported from libbe(3) so that
		 * the caller can determine if it needs to warn about the origin
		 * not being destroyed or not.
		 */
		if ((options & BE_DESTROY_AUTOORIGIN) != 0 && *origin != '\0' &&
		    be_is_auto_snapshot_name(lbh, origin))
			options |= BE_DESTROY_ORIGIN;

		/* Don't destroy a mounted dataset unless force is specified */
		if ((mounted = zfs_is_mounted(fs, NULL)) != 0) {
			if (force) {
				zfs_unmount(fs, NULL, 0);
			} else {
				free(bdd.snapname);
				return (set_error(lbh, BE_ERR_DESTROYMNT));
			}
		}
	} else {
		if (!zfs_dataset_exists(lbh->lzh, path, ZFS_TYPE_SNAPSHOT))
			return (set_error(lbh, BE_ERR_NOENT));

		bdd.snapname = strdup(snapdelim + 1);
		if (bdd.snapname == NULL)
			return (set_error(lbh, BE_ERR_NOMEM));
		*snapdelim = '\0';
		fs = zfs_open(lbh->lzh, path, ZFS_TYPE_DATASET);
		if (fs == NULL) {
			free(bdd.snapname);
			return (set_error(lbh, BE_ERR_ZFSOPEN));
		}
	}

	err = be_destroy_cb(fs, &bdd);
	zfs_close(fs);
	free(bdd.snapname);
	if (err != 0) {
		/* Children are still present or the mount is referenced */
		if (err == EBUSY)
			return (set_error(lbh, BE_ERR_DESTROYMNT));
		return (set_error(lbh, BE_ERR_UNKNOWN));
	}

	if ((options & BE_DESTROY_ORIGIN) == 0)
		return (0);

	/* The origin can't possibly be shorter than the BE root */
	rootlen = strlen(lbh->root);
	if (*origin == '\0' || strlen(origin) <= rootlen + 1)
		return (set_error(lbh, BE_ERR_INVORIGIN));

	/*
	 * We'll be chopping off the BE root and running this back through
	 * be_destroy, so that we properly handle the origin snapshot whether
	 * it be that of a deep BE or not.
	 */
	if (strncmp(origin, lbh->root, rootlen) != 0 || origin[rootlen] != '/')
		return (0);

	return (be_destroy(lbh, origin + rootlen + 1,
	    options & ~BE_DESTROY_ORIGIN));
}