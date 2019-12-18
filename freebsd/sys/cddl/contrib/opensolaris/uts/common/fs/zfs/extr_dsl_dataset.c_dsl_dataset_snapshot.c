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
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_3__ {int /*<<< orphan*/  ddsa_cr; int /*<<< orphan*/ * ddsa_errors; int /*<<< orphan*/ * ddsa_props; int /*<<< orphan*/ * ddsa_snaps; } ;
typedef  TYPE_1__ dsl_dataset_snapshot_arg_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRED () ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ SPA_VERSION_FAST_SNAP ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_NORMAL ; 
 int /*<<< orphan*/  dsl_dataset_snapshot_check ; 
 int /*<<< orphan*/  dsl_dataset_snapshot_sync ; 
 int dsl_sync_task (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,uintptr_t) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int fnvlist_num_pairs (int /*<<< orphan*/ *) ; 
 scalar_t__ fnvpair_value_uint64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_open (char*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  zil_resume (void*) ; 
 int zil_suspend (char*,void**) ; 
 int /*<<< orphan*/  zvol_create_minors (char*) ; 

int
dsl_dataset_snapshot(nvlist_t *snaps, nvlist_t *props, nvlist_t *errors)
{
	dsl_dataset_snapshot_arg_t ddsa;
	nvpair_t *pair;
	boolean_t needsuspend;
	int error;
	spa_t *spa;
	char *firstname;
	nvlist_t *suspended = NULL;

	pair = nvlist_next_nvpair(snaps, NULL);
	if (pair == NULL)
		return (0);
	firstname = nvpair_name(pair);

	error = spa_open(firstname, &spa, FTAG);
	if (error != 0)
		return (error);
	needsuspend = (spa_version(spa) < SPA_VERSION_FAST_SNAP);
	spa_close(spa, FTAG);

	if (needsuspend) {
		suspended = fnvlist_alloc();
		for (pair = nvlist_next_nvpair(snaps, NULL); pair != NULL;
		    pair = nvlist_next_nvpair(snaps, pair)) {
			char fsname[ZFS_MAX_DATASET_NAME_LEN];
			char *snapname = nvpair_name(pair);
			char *atp;
			void *cookie;

			atp = strchr(snapname, '@');
			if (atp == NULL) {
				error = SET_ERROR(EINVAL);
				break;
			}
			(void) strlcpy(fsname, snapname, atp - snapname + 1);

			error = zil_suspend(fsname, &cookie);
			if (error != 0)
				break;
			fnvlist_add_uint64(suspended, fsname,
			    (uintptr_t)cookie);
		}
	}

	ddsa.ddsa_snaps = snaps;
	ddsa.ddsa_props = props;
	ddsa.ddsa_errors = errors;
	ddsa.ddsa_cr = CRED();

	if (error == 0) {
		error = dsl_sync_task(firstname, dsl_dataset_snapshot_check,
		    dsl_dataset_snapshot_sync, &ddsa,
		    fnvlist_num_pairs(snaps) * 3, ZFS_SPACE_CHECK_NORMAL);
	}

	if (suspended != NULL) {
		for (pair = nvlist_next_nvpair(suspended, NULL); pair != NULL;
		    pair = nvlist_next_nvpair(suspended, pair)) {
			zil_resume((void *)(uintptr_t)
			    fnvpair_value_uint64(pair));
		}
		fnvlist_free(suspended);
	}

#ifdef __FreeBSD__
#ifdef _KERNEL
	if (error == 0) {
		for (pair = nvlist_next_nvpair(snaps, NULL); pair != NULL;
		    pair = nvlist_next_nvpair(snaps, pair)) {
			char *snapname = nvpair_name(pair);
			zvol_create_minors(snapname);
		}
	}
#endif
#endif
	return (error);
}