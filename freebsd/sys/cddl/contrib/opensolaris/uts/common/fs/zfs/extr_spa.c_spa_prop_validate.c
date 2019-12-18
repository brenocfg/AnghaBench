#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int zpool_prop_t ;
typedef  int uint64_t ;
struct TYPE_5__ {int spa_failmode; int /*<<< orphan*/  spa_root_vdev; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BOOTFS_COMPRESS_VALID (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DATA_TYPE_STRING ; 
 int /*<<< orphan*/  DATA_TYPE_UINT64 ; 
 int /*<<< orphan*/  DMU_OST_ZFS ; 
 int E2BIG ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int SPA_VERSION_BEFORE_FEATURES ; 
 int SPA_VERSION_BOOTFS ; 
 int SPA_VERSION_DEDUP ; 
 int /*<<< orphan*/  ZFS_PROP_COMPRESSION ; 
 int ZIO_DEDUPDITTO_MIN ; 
 int ZIO_FAILURE_MODE_PANIC ; 
 int ZIO_FAILURE_MODE_WAIT ; 
#define  ZPOOL_PROP_AUTOEXPAND 138 
#define  ZPOOL_PROP_AUTOREPLACE 137 
#define  ZPOOL_PROP_BOOTFS 136 
#define  ZPOOL_PROP_CACHEFILE 135 
#define  ZPOOL_PROP_COMMENT 134 
#define  ZPOOL_PROP_DEDUPDITTO 133 
#define  ZPOOL_PROP_DELEGATION 132 
#define  ZPOOL_PROP_FAILUREMODE 131 
#define  ZPOOL_PROP_INVAL 130 
#define  ZPOOL_PROP_LISTSNAPS 129 
#define  ZPOOL_PROP_VERSION 128 
 int /*<<< orphan*/  ZPROP_MAX_COMMENT ; 
 int /*<<< orphan*/  dmu_objset_ds (int /*<<< orphan*/ *) ; 
 int dmu_objset_hold (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int dmu_objset_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_type (int /*<<< orphan*/ *) ; 
 int dsl_prop_get_int_ds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nvlist_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_type (int /*<<< orphan*/ *) ; 
 int nvpair_value_string (int /*<<< orphan*/ *,char**) ; 
 int nvpair_value_uint64 (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  spa_suspended (TYPE_1__*) ; 
 int spa_version (TYPE_1__*) ; 
 int /*<<< orphan*/  strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  vdev_is_bootable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfeature_lookup_name (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 
 int zpool_name_to_prop (char const*) ; 
 int zpool_prop_default_numeric (int const) ; 
 int /*<<< orphan*/  zpool_prop_feature (char const*) ; 
 int /*<<< orphan*/  zpool_prop_to_name (int const) ; 

__attribute__((used)) static int
spa_prop_validate(spa_t *spa, nvlist_t *props)
{
	nvpair_t *elem;
	int error = 0, reset_bootfs = 0;
	uint64_t objnum = 0;
	boolean_t has_feature = B_FALSE;

	elem = NULL;
	while ((elem = nvlist_next_nvpair(props, elem)) != NULL) {
		uint64_t intval;
		char *strval, *slash, *check, *fname;
		const char *propname = nvpair_name(elem);
		zpool_prop_t prop = zpool_name_to_prop(propname);

		switch (prop) {
		case ZPOOL_PROP_INVAL:
			if (!zpool_prop_feature(propname)) {
				error = SET_ERROR(EINVAL);
				break;
			}

			/*
			 * Sanitize the input.
			 */
			if (nvpair_type(elem) != DATA_TYPE_UINT64) {
				error = SET_ERROR(EINVAL);
				break;
			}

			if (nvpair_value_uint64(elem, &intval) != 0) {
				error = SET_ERROR(EINVAL);
				break;
			}

			if (intval != 0) {
				error = SET_ERROR(EINVAL);
				break;
			}

			fname = strchr(propname, '@') + 1;
			if (zfeature_lookup_name(fname, NULL) != 0) {
				error = SET_ERROR(EINVAL);
				break;
			}

			has_feature = B_TRUE;
			break;

		case ZPOOL_PROP_VERSION:
			error = nvpair_value_uint64(elem, &intval);
			if (!error &&
			    (intval < spa_version(spa) ||
			    intval > SPA_VERSION_BEFORE_FEATURES ||
			    has_feature))
				error = SET_ERROR(EINVAL);
			break;

		case ZPOOL_PROP_DELEGATION:
		case ZPOOL_PROP_AUTOREPLACE:
		case ZPOOL_PROP_LISTSNAPS:
		case ZPOOL_PROP_AUTOEXPAND:
			error = nvpair_value_uint64(elem, &intval);
			if (!error && intval > 1)
				error = SET_ERROR(EINVAL);
			break;

		case ZPOOL_PROP_BOOTFS:
			/*
			 * If the pool version is less than SPA_VERSION_BOOTFS,
			 * or the pool is still being created (version == 0),
			 * the bootfs property cannot be set.
			 */
			if (spa_version(spa) < SPA_VERSION_BOOTFS) {
				error = SET_ERROR(ENOTSUP);
				break;
			}

			/*
			 * Make sure the vdev config is bootable
			 */
			if (!vdev_is_bootable(spa->spa_root_vdev)) {
				error = SET_ERROR(ENOTSUP);
				break;
			}

			reset_bootfs = 1;

			error = nvpair_value_string(elem, &strval);

			if (!error) {
				objset_t *os;
				uint64_t propval;

				if (strval == NULL || strval[0] == '\0') {
					objnum = zpool_prop_default_numeric(
					    ZPOOL_PROP_BOOTFS);
					break;
				}

				error = dmu_objset_hold(strval, FTAG, &os);
				if (error != 0)
					break;

				/*
				 * Must be ZPL, and its property settings
				 * must be supported.
				 */

				if (dmu_objset_type(os) != DMU_OST_ZFS) {
					error = SET_ERROR(ENOTSUP);
				} else if ((error =
				    dsl_prop_get_int_ds(dmu_objset_ds(os),
				    zfs_prop_to_name(ZFS_PROP_COMPRESSION),
				    &propval)) == 0 &&
				    !BOOTFS_COMPRESS_VALID(propval)) {
					error = SET_ERROR(ENOTSUP);
				} else {
					objnum = dmu_objset_id(os);
				}
				dmu_objset_rele(os, FTAG);
			}
			break;

		case ZPOOL_PROP_FAILUREMODE:
			error = nvpair_value_uint64(elem, &intval);
			if (!error && (intval < ZIO_FAILURE_MODE_WAIT ||
			    intval > ZIO_FAILURE_MODE_PANIC))
				error = SET_ERROR(EINVAL);

			/*
			 * This is a special case which only occurs when
			 * the pool has completely failed. This allows
			 * the user to change the in-core failmode property
			 * without syncing it out to disk (I/Os might
			 * currently be blocked). We do this by returning
			 * EIO to the caller (spa_prop_set) to trick it
			 * into thinking we encountered a property validation
			 * error.
			 */
			if (!error && spa_suspended(spa)) {
				spa->spa_failmode = intval;
				error = SET_ERROR(EIO);
			}
			break;

		case ZPOOL_PROP_CACHEFILE:
			if ((error = nvpair_value_string(elem, &strval)) != 0)
				break;

			if (strval[0] == '\0')
				break;

			if (strcmp(strval, "none") == 0)
				break;

			if (strval[0] != '/') {
				error = SET_ERROR(EINVAL);
				break;
			}

			slash = strrchr(strval, '/');
			ASSERT(slash != NULL);

			if (slash[1] == '\0' || strcmp(slash, "/.") == 0 ||
			    strcmp(slash, "/..") == 0)
				error = SET_ERROR(EINVAL);
			break;

		case ZPOOL_PROP_COMMENT:
			if ((error = nvpair_value_string(elem, &strval)) != 0)
				break;
			for (check = strval; *check != '\0'; check++) {
				/*
				 * The kernel doesn't have an easy isprint()
				 * check.  For this kernel check, we merely
				 * check ASCII apart from DEL.  Fix this if
				 * there is an easy-to-use kernel isprint().
				 */
				if (*check >= 0x7f) {
					error = SET_ERROR(EINVAL);
					break;
				}
			}
			if (strlen(strval) > ZPROP_MAX_COMMENT)
				error = E2BIG;
			break;

		case ZPOOL_PROP_DEDUPDITTO:
			if (spa_version(spa) < SPA_VERSION_DEDUP)
				error = SET_ERROR(ENOTSUP);
			else
				error = nvpair_value_uint64(elem, &intval);
			if (error == 0 &&
			    intval != 0 && intval < ZIO_DEDUPDITTO_MIN)
				error = SET_ERROR(EINVAL);
			break;
		}

		if (error)
			break;
	}

	if (!error && reset_bootfs) {
		error = nvlist_remove(props,
		    zpool_prop_to_name(ZPOOL_PROP_BOOTFS), DATA_TYPE_STRING);

		if (!error) {
			error = nvlist_add_uint64(props,
			    zpool_prop_to_name(ZPOOL_PROP_BOOTFS), objnum);
		}
	}

	return (error);
}