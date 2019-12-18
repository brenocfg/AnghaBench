#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int zfs_prop_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRED () ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  INGLOBALZONE (int /*<<< orphan*/ ) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
#define  ZFS_PROP_FILESYSTEM_LIMIT 132 
#define  ZFS_PROP_MLSLABEL 131 
#define  ZFS_PROP_QUOTA 130 
#define  ZFS_PROP_SNAPSHOT_LIMIT 129 
#define  ZFS_PROP_ZONED 128 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  dsl_prop_get_integer (char const*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  is_system_labeled () ; 
 int /*<<< orphan*/  nvpair_value_string (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int) ; 
 int zfs_secpolicy_write_perms (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zfs_set_slabel_policy (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_secpolicy_setprop(const char *dsname, zfs_prop_t prop, nvpair_t *propval,
    cred_t *cr)
{
	char *strval;

	/*
	 * Check permissions for special properties.
	 */
	switch (prop) {
	case ZFS_PROP_ZONED:
		/*
		 * Disallow setting of 'zoned' from within a local zone.
		 */
		if (!INGLOBALZONE(curthread))
			return (SET_ERROR(EPERM));
		break;

	case ZFS_PROP_QUOTA:
	case ZFS_PROP_FILESYSTEM_LIMIT:
	case ZFS_PROP_SNAPSHOT_LIMIT:
		if (!INGLOBALZONE(curthread)) {
			uint64_t zoned;
			char setpoint[ZFS_MAX_DATASET_NAME_LEN];
			/*
			 * Unprivileged users are allowed to modify the
			 * limit on things *under* (ie. contained by)
			 * the thing they own.
			 */
			if (dsl_prop_get_integer(dsname, "jailed", &zoned,
			    setpoint))
				return (SET_ERROR(EPERM));
			if (!zoned || strlen(dsname) <= strlen(setpoint))
				return (SET_ERROR(EPERM));
		}
		break;

	case ZFS_PROP_MLSLABEL:
#ifdef SECLABEL
		if (!is_system_labeled())
			return (SET_ERROR(EPERM));

		if (nvpair_value_string(propval, &strval) == 0) {
			int err;

			err = zfs_set_slabel_policy(dsname, strval, CRED());
			if (err != 0)
				return (err);
		}
#else
		return (EOPNOTSUPP);
#endif
		break;
	}

	return (zfs_secpolicy_write_perms(dsname, zfs_prop_to_name(prop), cr));
}