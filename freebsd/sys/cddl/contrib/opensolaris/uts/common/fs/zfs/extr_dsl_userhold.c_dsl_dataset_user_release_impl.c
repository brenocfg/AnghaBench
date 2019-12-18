#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_9__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_10__ {int (* ddura_holdfunc ) (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ;void* ddura_chkholds; void* ddura_todelete; int /*<<< orphan*/ * ddura_errlist; int /*<<< orphan*/ * ddura_holds; } ;
typedef  TYPE_2__ dsl_dataset_user_release_arg_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_EXTRA_RESERVED ; 
 int dsl_dataset_hold (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int dsl_dataset_hold_obj_string (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_user_release_check ; 
 int /*<<< orphan*/  dsl_dataset_user_release_sync ; 
 int /*<<< orphan*/  dsl_pool_config_enter (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_exit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int dsl_sync_task (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (void*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 char* spa_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_unmount_snap (char*) ; 

__attribute__((used)) static int
dsl_dataset_user_release_impl(nvlist_t *holds, nvlist_t *errlist,
    dsl_pool_t *tmpdp)
{
	dsl_dataset_user_release_arg_t ddura;
	nvpair_t *pair;
	char *pool;
	int error;

	pair = nvlist_next_nvpair(holds, NULL);
	if (pair == NULL)
		return (0);

	/*
	 * The release may cause snapshots to be destroyed; make sure they
	 * are not mounted.
	 */
	if (tmpdp != NULL) {
		/* Temporary holds are specified by dsobj string. */
		ddura.ddura_holdfunc = dsl_dataset_hold_obj_string;
		pool = spa_name(tmpdp->dp_spa);
#ifdef _KERNEL
		for (pair = nvlist_next_nvpair(holds, NULL); pair != NULL;
		    pair = nvlist_next_nvpair(holds, pair)) {
			dsl_dataset_t *ds;

			dsl_pool_config_enter(tmpdp, FTAG);
			error = dsl_dataset_hold_obj_string(tmpdp,
			    nvpair_name(pair), FTAG, &ds);
			if (error == 0) {
				char name[ZFS_MAX_DATASET_NAME_LEN];
				dsl_dataset_name(ds, name);
				dsl_pool_config_exit(tmpdp, FTAG);
				dsl_dataset_rele(ds, FTAG);
				(void) zfs_unmount_snap(name);
			} else {
				dsl_pool_config_exit(tmpdp, FTAG);
			}
		}
#endif
	} else {
		/* Non-temporary holds are specified by name. */
		ddura.ddura_holdfunc = dsl_dataset_hold;
		pool = nvpair_name(pair);
#ifdef _KERNEL
		for (pair = nvlist_next_nvpair(holds, NULL); pair != NULL;
		    pair = nvlist_next_nvpair(holds, pair)) {
			(void) zfs_unmount_snap(nvpair_name(pair));
		}
#endif
	}

	ddura.ddura_holds = holds;
	ddura.ddura_errlist = errlist;
	ddura.ddura_todelete = fnvlist_alloc();
	ddura.ddura_chkholds = fnvlist_alloc();

	error = dsl_sync_task(pool, dsl_dataset_user_release_check,
	    dsl_dataset_user_release_sync, &ddura, 0,
	    ZFS_SPACE_CHECK_EXTRA_RESERVED);
	fnvlist_free(ddura.ddura_todelete);
	fnvlist_free(ddura.ddura_chkholds);

	return (error);
}