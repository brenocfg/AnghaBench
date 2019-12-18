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
typedef  int zfs_prop_t ;
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  spa_feature_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {int ci_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOTFS_COMPRESS_VALID (size_t) ; 
 int /*<<< orphan*/  CRED () ; 
 scalar_t__ DATA_TYPE_NVLIST ; 
 scalar_t__ DATA_TYPE_UINT64 ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_FEATURE_LARGE_BLOCKS ; 
 int /*<<< orphan*/  SPA_FEATURE_LARGE_DNODE ; 
 int /*<<< orphan*/  SPA_FEATURE_LZ4_COMPRESS ; 
 int /*<<< orphan*/  SPA_FEATURE_NONE ; 
 size_t SPA_MAXBLOCKSIZE ; 
 size_t SPA_OLD_MAXBLOCKSIZE ; 
 int /*<<< orphan*/  SPA_VERSION_DEDUP ; 
 int /*<<< orphan*/  SPA_VERSION_DITTO_BLOCKS ; 
 int /*<<< orphan*/  SPA_VERSION_GZIP_COMPRESSION ; 
 int /*<<< orphan*/  SPA_VERSION_PASSTHROUGH_X ; 
 int /*<<< orphan*/  SPA_VERSION_ZLE_COMPRESSION ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ZCHECKSUM_FLAG_SALTED ; 
 size_t ZFS_ACL_PASSTHROUGH_X ; 
 char* ZFS_DELEG_PERM_GROUPQUOTA ; 
 char const* ZFS_DELEG_PERM_USERPROP ; 
 char* ZFS_DELEG_PERM_USERQUOTA ; 
 size_t ZFS_DNSIZE_LEGACY ; 
#define  ZFS_PROP_ACLINHERIT 135 
#define  ZFS_PROP_CHECKSUM 134 
#define  ZFS_PROP_COMPRESSION 133 
#define  ZFS_PROP_COPIES 132 
#define  ZFS_PROP_DEDUP 131 
#define  ZFS_PROP_DNODESIZE 130 
 size_t ZFS_PROP_GROUPQUOTA ; 
#define  ZFS_PROP_RECORDSIZE 129 
#define  ZFS_PROP_SHARESMB 128 
 size_t ZFS_PROP_USERQUOTA ; 
 size_t ZIO_CHECKSUM_FUNCTIONS ; 
 size_t ZIO_CHECKSUM_MASK ; 
 size_t ZIO_COMPRESS_GZIP_1 ; 
 size_t ZIO_COMPRESS_GZIP_9 ; 
 size_t ZIO_COMPRESS_LZ4 ; 
 size_t ZIO_COMPRESS_ZLE ; 
 int /*<<< orphan*/  ZPL_VERSION_FUID ; 
 int ZPROP_INVAL ; 
 int /*<<< orphan*/  ZPROP_VALUE ; 
 scalar_t__ nvlist_lookup_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_type (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvpair_value_uint64 (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  spa_bootfs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_is_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_open (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_earlier_version (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_is_bootfs (char const*) ; 
 size_t zfs_max_recordsize ; 
 int zfs_name_to_prop (char const*) ; 
 scalar_t__ zfs_prop_user (char const*) ; 
 scalar_t__ zfs_prop_userquota (char const*) ; 
 int zfs_secpolicy_setprop (char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zfs_secpolicy_write_perms (char const*,char const*,int /*<<< orphan*/ *) ; 
 char** zfs_userquota_prop_prefixes ; 
 TYPE_1__* zio_checksum_table ; 
 int /*<<< orphan*/  zio_checksum_to_feature (size_t) ; 
 int /*<<< orphan*/  zpl_earlier_version (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_check_settable(const char *dsname, nvpair_t *pair, cred_t *cr)
{
	const char *propname = nvpair_name(pair);
	boolean_t issnap = (strchr(dsname, '@') != NULL);
	zfs_prop_t prop = zfs_name_to_prop(propname);
	uint64_t intval;
	int err;

	if (prop == ZPROP_INVAL) {
		if (zfs_prop_user(propname)) {
			if (err = zfs_secpolicy_write_perms(dsname,
			    ZFS_DELEG_PERM_USERPROP, cr))
				return (err);
			return (0);
		}

		if (!issnap && zfs_prop_userquota(propname)) {
			const char *perm = NULL;
			const char *uq_prefix =
			    zfs_userquota_prop_prefixes[ZFS_PROP_USERQUOTA];
			const char *gq_prefix =
			    zfs_userquota_prop_prefixes[ZFS_PROP_GROUPQUOTA];

			if (strncmp(propname, uq_prefix,
			    strlen(uq_prefix)) == 0) {
				perm = ZFS_DELEG_PERM_USERQUOTA;
			} else if (strncmp(propname, gq_prefix,
			    strlen(gq_prefix)) == 0) {
				perm = ZFS_DELEG_PERM_GROUPQUOTA;
			} else {
				/* USERUSED and GROUPUSED are read-only */
				return (SET_ERROR(EINVAL));
			}

			if (err = zfs_secpolicy_write_perms(dsname, perm, cr))
				return (err);
			return (0);
		}

		return (SET_ERROR(EINVAL));
	}

	if (issnap)
		return (SET_ERROR(EINVAL));

	if (nvpair_type(pair) == DATA_TYPE_NVLIST) {
		/*
		 * dsl_prop_get_all_impl() returns properties in this
		 * format.
		 */
		nvlist_t *attrs;
		VERIFY(nvpair_value_nvlist(pair, &attrs) == 0);
		VERIFY(nvlist_lookup_nvpair(attrs, ZPROP_VALUE,
		    &pair) == 0);
	}

	/*
	 * Check that this value is valid for this pool version
	 */
	switch (prop) {
	case ZFS_PROP_COMPRESSION:
		/*
		 * If the user specified gzip compression, make sure
		 * the SPA supports it. We ignore any errors here since
		 * we'll catch them later.
		 */
		if (nvpair_value_uint64(pair, &intval) == 0) {
			if (intval >= ZIO_COMPRESS_GZIP_1 &&
			    intval <= ZIO_COMPRESS_GZIP_9 &&
			    zfs_earlier_version(dsname,
			    SPA_VERSION_GZIP_COMPRESSION)) {
				return (SET_ERROR(ENOTSUP));
			}

			if (intval == ZIO_COMPRESS_ZLE &&
			    zfs_earlier_version(dsname,
			    SPA_VERSION_ZLE_COMPRESSION))
				return (SET_ERROR(ENOTSUP));

			if (intval == ZIO_COMPRESS_LZ4) {
				spa_t *spa;

				if ((err = spa_open(dsname, &spa, FTAG)) != 0)
					return (err);

				if (!spa_feature_is_enabled(spa,
				    SPA_FEATURE_LZ4_COMPRESS)) {
					spa_close(spa, FTAG);
					return (SET_ERROR(ENOTSUP));
				}
				spa_close(spa, FTAG);
			}

			/*
			 * If this is a bootable dataset then
			 * verify that the compression algorithm
			 * is supported for booting. We must return
			 * something other than ENOTSUP since it
			 * implies a downrev pool version.
			 */
			if (zfs_is_bootfs(dsname) &&
			    !BOOTFS_COMPRESS_VALID(intval)) {
				return (SET_ERROR(ERANGE));
			}
		}
		break;

	case ZFS_PROP_COPIES:
		if (zfs_earlier_version(dsname, SPA_VERSION_DITTO_BLOCKS))
			return (SET_ERROR(ENOTSUP));
		break;

	case ZFS_PROP_RECORDSIZE:
		/* Record sizes above 128k need the feature to be enabled */
		if (nvpair_value_uint64(pair, &intval) == 0 &&
		    intval > SPA_OLD_MAXBLOCKSIZE) {
			spa_t *spa;

			/*
			 * We don't allow setting the property above 1MB,
			 * unless the tunable has been changed.
			 */
			if (intval > zfs_max_recordsize ||
			    intval > SPA_MAXBLOCKSIZE)
				return (SET_ERROR(ERANGE));

			if ((err = spa_open(dsname, &spa, FTAG)) != 0)
				return (err);

			if (!spa_feature_is_enabled(spa,
			    SPA_FEATURE_LARGE_BLOCKS)) {
				spa_close(spa, FTAG);
				return (SET_ERROR(ENOTSUP));
			}
			spa_close(spa, FTAG);
		}
		break;

	case ZFS_PROP_DNODESIZE:
		/* Dnode sizes above 512 need the feature to be enabled */
		if (nvpair_value_uint64(pair, &intval) == 0 &&
		    intval != ZFS_DNSIZE_LEGACY) {
			spa_t *spa;

			if ((err = spa_open(dsname, &spa, FTAG)) != 0)
				return (err);

			if (!spa_feature_is_enabled(spa,
			    SPA_FEATURE_LARGE_DNODE)) {
				spa_close(spa, FTAG);
				return (SET_ERROR(ENOTSUP));
			}
			spa_close(spa, FTAG);
		}
		break;

	case ZFS_PROP_SHARESMB:
		if (zpl_earlier_version(dsname, ZPL_VERSION_FUID))
			return (SET_ERROR(ENOTSUP));
		break;

	case ZFS_PROP_ACLINHERIT:
		if (nvpair_type(pair) == DATA_TYPE_UINT64 &&
		    nvpair_value_uint64(pair, &intval) == 0) {
			if (intval == ZFS_ACL_PASSTHROUGH_X &&
			    zfs_earlier_version(dsname,
			    SPA_VERSION_PASSTHROUGH_X))
				return (SET_ERROR(ENOTSUP));
		}
		break;

	case ZFS_PROP_CHECKSUM:
	case ZFS_PROP_DEDUP:
	{
		spa_feature_t feature;
		spa_t *spa;

		/* dedup feature version checks */
		if (prop == ZFS_PROP_DEDUP &&
		    zfs_earlier_version(dsname, SPA_VERSION_DEDUP))
			return (SET_ERROR(ENOTSUP));

		if (nvpair_value_uint64(pair, &intval) != 0)
			return (SET_ERROR(EINVAL));

		/* check prop value is enabled in features */
		feature = zio_checksum_to_feature(intval & ZIO_CHECKSUM_MASK);
		if (feature == SPA_FEATURE_NONE)
			break;

		if ((err = spa_open(dsname, &spa, FTAG)) != 0)
			return (err);
		/*
		 * Salted checksums are not supported on root pools.
		 */
		if (spa_bootfs(spa) != 0 &&
		    intval < ZIO_CHECKSUM_FUNCTIONS &&
		    (zio_checksum_table[intval].ci_flags &
		    ZCHECKSUM_FLAG_SALTED)) {
			spa_close(spa, FTAG);
			return (SET_ERROR(ERANGE));
		}
		if (!spa_feature_is_enabled(spa, feature)) {
			spa_close(spa, FTAG);
			return (SET_ERROR(ENOTSUP));
		}
		spa_close(spa, FTAG);
		break;
	}
	}

	return (zfs_secpolicy_setprop(dsname, prop, pair, CRED()));
}