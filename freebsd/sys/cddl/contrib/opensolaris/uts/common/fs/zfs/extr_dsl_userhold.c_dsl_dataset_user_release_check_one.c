#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_13__ {int /*<<< orphan*/  ddura_chkholds; int /*<<< orphan*/ * ddura_todelete; int /*<<< orphan*/ * ddura_errlist; } ;
typedef  TYPE_3__ dsl_dataset_user_release_arg_t ;
struct TYPE_14__ {int ds_userrefs; TYPE_2__* ds_dir; int /*<<< orphan*/  ds_is_snapshot; } ;
typedef  TYPE_4__ dsl_dataset_t ;
struct TYPE_15__ {scalar_t__ ds_userrefs_obj; int ds_num_children; } ;
struct TYPE_12__ {TYPE_1__* dd_pool; } ;
struct TYPE_11__ {int /*<<< orphan*/ * dp_meta_objset; } ;

/* Variables and functions */
 scalar_t__ DS_IS_DEFER_DESTROY (TYPE_4__*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOENT ; 
 int SET_ERROR (int) ; 
 scalar_t__ dsl_dataset_long_held (TYPE_4__*) ; 
 TYPE_7__* dsl_dataset_phys (TYPE_4__*) ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fnvlist_add_int32 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 char* kmem_asprintf (char*,char const*,char const*) ; 
 scalar_t__ nvlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strfree (char*) ; 
 int zap_lookup (int /*<<< orphan*/ *,scalar_t__,char const*,int,int,scalar_t__*) ; 

__attribute__((used)) static int
dsl_dataset_user_release_check_one(dsl_dataset_user_release_arg_t *ddura,
    dsl_dataset_t *ds, nvlist_t *holds, const char *snapname)
{
	uint64_t zapobj;
	nvlist_t *holds_found;
	objset_t *mos;
	int numholds;

	if (!ds->ds_is_snapshot)
		return (SET_ERROR(EINVAL));

	if (nvlist_empty(holds))
		return (0);

	numholds = 0;
	mos = ds->ds_dir->dd_pool->dp_meta_objset;
	zapobj = dsl_dataset_phys(ds)->ds_userrefs_obj;
	holds_found = fnvlist_alloc();

	for (nvpair_t *pair = nvlist_next_nvpair(holds, NULL); pair != NULL;
	    pair = nvlist_next_nvpair(holds, pair)) {
		uint64_t tmp;
		int error;
		const char *holdname = nvpair_name(pair);

		if (zapobj != 0)
			error = zap_lookup(mos, zapobj, holdname, 8, 1, &tmp);
		else
			error = SET_ERROR(ENOENT);

		/*
		 * Non-existent holds are put on the errlist, but don't
		 * cause an overall failure.
		 */
		if (error == ENOENT) {
			if (ddura->ddura_errlist != NULL) {
				char *errtag = kmem_asprintf("%s#%s",
				    snapname, holdname);
				fnvlist_add_int32(ddura->ddura_errlist, errtag,
				    ENOENT);
				strfree(errtag);
			}
			continue;
		}

		if (error != 0) {
			fnvlist_free(holds_found);
			return (error);
		}

		fnvlist_add_boolean(holds_found, holdname);
		numholds++;
	}

	if (DS_IS_DEFER_DESTROY(ds) &&
	    dsl_dataset_phys(ds)->ds_num_children == 1 &&
	    ds->ds_userrefs == numholds) {
		/* we need to destroy the snapshot as well */
		if (dsl_dataset_long_held(ds)) {
			fnvlist_free(holds_found);
			return (SET_ERROR(EBUSY));
		}
		fnvlist_add_boolean(ddura->ddura_todelete, snapname);
	}

	if (numholds != 0) {
		fnvlist_add_nvlist(ddura->ddura_chkholds, snapname,
		    holds_found);
	}
	fnvlist_free(holds_found);

	return (0);
}