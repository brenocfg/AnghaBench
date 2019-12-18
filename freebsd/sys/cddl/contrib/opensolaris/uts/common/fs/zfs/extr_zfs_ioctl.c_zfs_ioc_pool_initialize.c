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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  guid_as_str ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FTAG ; 
 int MAXNAMELEN ; 
 scalar_t__ POOL_INITIALIZE_CANCEL ; 
 scalar_t__ POOL_INITIALIZE_DO ; 
 scalar_t__ POOL_INITIALIZE_SUSPEND ; 
 int SET_ERROR (int) ; 
 int /*<<< orphan*/  ZPOOL_INITIALIZE_COMMAND ; 
 int /*<<< orphan*/  ZPOOL_INITIALIZE_VDEVS ; 
 int /*<<< orphan*/  fnvlist_add_int64 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ fnvlist_size (int /*<<< orphan*/ *) ; 
 scalar_t__ fnvpair_value_uint64 (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long long) ; 
 int /*<<< orphan*/  spa_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_open (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int spa_vdev_initialize (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
zfs_ioc_pool_initialize(const char *poolname, nvlist_t *innvl, nvlist_t *outnvl)
{
	spa_t *spa;
	int error;

	error = spa_open(poolname, &spa, FTAG);
	if (error != 0)
		return (error);

	uint64_t cmd_type;
	if (nvlist_lookup_uint64(innvl, ZPOOL_INITIALIZE_COMMAND,
	    &cmd_type) != 0) {
		spa_close(spa, FTAG);
		return (SET_ERROR(EINVAL));
	}
	if (!(cmd_type == POOL_INITIALIZE_CANCEL ||
	    cmd_type == POOL_INITIALIZE_DO ||
	    cmd_type == POOL_INITIALIZE_SUSPEND)) {
		spa_close(spa, FTAG);
		return (SET_ERROR(EINVAL));
	}

	nvlist_t *vdev_guids;
	if (nvlist_lookup_nvlist(innvl, ZPOOL_INITIALIZE_VDEVS,
	    &vdev_guids) != 0) {
		spa_close(spa, FTAG);
		return (SET_ERROR(EINVAL));
	}

	nvlist_t *vdev_errlist = fnvlist_alloc();
	int total_errors = 0;

	for (nvpair_t *pair = nvlist_next_nvpair(vdev_guids, NULL);
	    pair != NULL; pair = nvlist_next_nvpair(vdev_guids, pair)) {
		uint64_t vdev_guid = fnvpair_value_uint64(pair);

		error = spa_vdev_initialize(spa, vdev_guid, cmd_type);
		if (error != 0) {
			char guid_as_str[MAXNAMELEN];

			(void) snprintf(guid_as_str, sizeof (guid_as_str),
			    "%llu", (unsigned long long)vdev_guid);
			fnvlist_add_int64(vdev_errlist, guid_as_str, error);
			total_errors++;
		}
	}
	if (fnvlist_size(vdev_errlist) > 0) {
		fnvlist_add_nvlist(outnvl, ZPOOL_INITIALIZE_VDEVS,
		    vdev_errlist);
	}
	fnvlist_free(vdev_errlist);

	spa_close(spa, FTAG);
	return (total_errors > 0 ? EINVAL : 0);
}