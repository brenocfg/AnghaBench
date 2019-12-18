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
struct TYPE_3__ {int zc_cookie; char* zc_name; char* zc_value; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  scalar_t__ dmu_objset_type_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int B_TRUE ; 
 scalar_t__ DMU_OST_ZFS ; 
 scalar_t__ DMU_OST_ZVOL ; 
 int /*<<< orphan*/  DS_FIND_CHILDREN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  EXDEV ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ dataset_namecheck (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dmu_objset_find (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int dmu_objset_hold (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_objset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dmu_objset_type (int /*<<< orphan*/ *) ; 
 int dsl_bookmark_rename (char*,char*,char*) ; 
 int dsl_dataset_rename_snapshot (char*,char*,char*,int) ; 
 int dsl_dir_rename (char*,char*) ; 
 int /*<<< orphan*/  recursive_unmount ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  zvol_remove_minor (char*) ; 

__attribute__((used)) static int
zfs_ioc_rename(zfs_cmd_t *zc)
{
	objset_t *os;
	dmu_objset_type_t ost;
	boolean_t recursive = zc->zc_cookie & 1;
	char *pos, *pos2;
	boolean_t allow_mounted = B_TRUE;
	int err;

#ifdef __FreeBSD__
	allow_mounted = (zc->zc_cookie & 2) != 0;
#endif

	zc->zc_name[sizeof (zc->zc_name) - 1] = '\0';
	zc->zc_value[sizeof (zc->zc_value) - 1] = '\0';

	pos = strchr(zc->zc_name, '#');
	if (pos != NULL) {
		/* Bookmarks must be in same fs. */
		pos2 = strchr(zc->zc_value, '#');
		if (pos2 == NULL)
			return (SET_ERROR(EINVAL));

		/* Recursive flag is not supported yet. */
		if (recursive)
			return (SET_ERROR(ENOTSUP));

		*pos = '\0';
		*pos2 = '\0';
		if (strcmp(zc->zc_name, zc->zc_value) == 0) {
			err = dsl_bookmark_rename(zc->zc_name,
			    pos + 1, pos2 + 1);
		} else {
			err = SET_ERROR(EXDEV);
		}
		*pos = '#';
		*pos2 = '#';
		return (err);
	}

	/* "zfs rename" from and to ...%recv datasets should both fail */
	if (dataset_namecheck(zc->zc_name, NULL, NULL) != 0 ||
	    dataset_namecheck(zc->zc_value, NULL, NULL) != 0 ||
	    strchr(zc->zc_name, '%') || strchr(zc->zc_value, '%'))
		return (SET_ERROR(EINVAL));

	err = dmu_objset_hold(zc->zc_name, FTAG, &os);
	if (err != 0)
		return (err);
	ost = dmu_objset_type(os);
	dmu_objset_rele(os, FTAG);

	pos = strchr(zc->zc_name, '@');
	if (pos != NULL) {
		/* Snapshots must be in same fs. */
		pos2 = strchr(zc->zc_value, '@');
		if (pos2 == NULL)
			return (SET_ERROR(EINVAL));
		*pos = '\0';
		*pos2 = '\0';
		if (strcmp(zc->zc_name, zc->zc_value) != 0) {
			err = SET_ERROR(EXDEV);
		} else {
			if (ost == DMU_OST_ZFS && !allow_mounted) {
				err = dmu_objset_find(zc->zc_name,
				    recursive_unmount, pos + 1,
				    recursive ? DS_FIND_CHILDREN : 0);
			}
			if (err == 0) {
				err = dsl_dataset_rename_snapshot(zc->zc_name,
				    pos + 1, pos2 + 1, recursive);
			}
		}
		*pos = '@';
		*pos2 = '@';
		return (err);
	} else {
#ifdef illumos
		if (ost == DMU_OST_ZVOL)
			(void) zvol_remove_minor(zc->zc_name);
#endif
		return (dsl_dir_rename(zc->zc_name, zc->zc_value));
	}
}