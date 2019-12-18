#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_25__ {TYPE_3__* dp_origin_snap; int /*<<< orphan*/  dp_meta_objset; } ;
typedef  TYPE_4__ dsl_pool_t ;
struct TYPE_26__ {TYPE_1__* ds_prev; TYPE_9__* ds_dir; } ;
typedef  TYPE_5__ dsl_dataset_t ;
struct TYPE_27__ {scalar_t__ drba_snapobj; TYPE_2__* drba_cookie; int /*<<< orphan*/  drba_cred; } ;
typedef  TYPE_6__ dmu_recv_begin_arg_t ;
struct TYPE_28__ {TYPE_4__* dd_pool; } ;
struct TYPE_24__ {scalar_t__ ds_object; } ;
struct TYPE_23__ {scalar_t__ drc_force; int /*<<< orphan*/  drc_tosnap; } ;
struct TYPE_22__ {scalar_t__ ds_object; } ;
struct TYPE_21__ {scalar_t__ ds_prev_snap_obj; scalar_t__ ds_guid; int /*<<< orphan*/  ds_snapnames_zapobj; } ;
struct TYPE_20__ {int /*<<< orphan*/  dd_child_dir_zapobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  ENODEV ; 
 int ENOENT ; 
 int /*<<< orphan*/  ETXTBSY ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_PROP_SNAPSHOT_LIMIT ; 
 scalar_t__ dsl_dataset_has_resume_receive_state (TYPE_5__*) ; 
 int dsl_dataset_hold_obj (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ,TYPE_5__**) ; 
 scalar_t__ dsl_dataset_modified_since_snap (TYPE_5__*,TYPE_5__*) ; 
 TYPE_13__* dsl_dataset_phys (TYPE_5__*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_10__* dsl_dir_phys (TYPE_9__*) ; 
 int dsl_fs_ss_limit_check (TYPE_9__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recv_clone_name ; 
 int zap_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 

__attribute__((used)) static int
recv_begin_check_existing_impl(dmu_recv_begin_arg_t *drba, dsl_dataset_t *ds,
    uint64_t fromguid)
{
	uint64_t val;
	int error;
	dsl_pool_t *dp = ds->ds_dir->dd_pool;

	/* Temporary clone name must not exist. */
	error = zap_lookup(dp->dp_meta_objset,
	    dsl_dir_phys(ds->ds_dir)->dd_child_dir_zapobj, recv_clone_name,
	    8, 1, &val);
	if (error != ENOENT)
		return (error == 0 ? SET_ERROR(EBUSY) : error);

	/* Resume state must not be set. */
	if (dsl_dataset_has_resume_receive_state(ds))
		return (SET_ERROR(EBUSY));

	/* New snapshot name must not exist. */
	error = zap_lookup(dp->dp_meta_objset,
	    dsl_dataset_phys(ds)->ds_snapnames_zapobj,
	    drba->drba_cookie->drc_tosnap, 8, 1, &val);
	if (error != ENOENT)
		return (error == 0 ? SET_ERROR(EEXIST) : error);

	/*
	 * Check snapshot limit before receiving. We'll recheck again at the
	 * end, but might as well abort before receiving if we're already over
	 * the limit.
	 *
	 * Note that we do not check the file system limit with
	 * dsl_dir_fscount_check because the temporary %clones don't count
	 * against that limit.
	 */
	error = dsl_fs_ss_limit_check(ds->ds_dir, 1, ZFS_PROP_SNAPSHOT_LIMIT,
	    NULL, drba->drba_cred);
	if (error != 0)
		return (error);

	if (fromguid != 0) {
		dsl_dataset_t *snap;
		uint64_t obj = dsl_dataset_phys(ds)->ds_prev_snap_obj;

		/* Find snapshot in this dir that matches fromguid. */
		while (obj != 0) {
			error = dsl_dataset_hold_obj(dp, obj, FTAG,
			    &snap);
			if (error != 0)
				return (SET_ERROR(ENODEV));
			if (snap->ds_dir != ds->ds_dir) {
				dsl_dataset_rele(snap, FTAG);
				return (SET_ERROR(ENODEV));
			}
			if (dsl_dataset_phys(snap)->ds_guid == fromguid)
				break;
			obj = dsl_dataset_phys(snap)->ds_prev_snap_obj;
			dsl_dataset_rele(snap, FTAG);
		}
		if (obj == 0)
			return (SET_ERROR(ENODEV));

		if (drba->drba_cookie->drc_force) {
			drba->drba_snapobj = obj;
		} else {
			/*
			 * If we are not forcing, there must be no
			 * changes since fromsnap.
			 */
			if (dsl_dataset_modified_since_snap(ds, snap)) {
				dsl_dataset_rele(snap, FTAG);
				return (SET_ERROR(ETXTBSY));
			}
			drba->drba_snapobj = ds->ds_prev->ds_object;
		}

		dsl_dataset_rele(snap, FTAG);
	} else {
		/* if full, then must be forced */
		if (!drba->drba_cookie->drc_force)
			return (SET_ERROR(EEXIST));
		/* start from $ORIGIN@$ORIGIN, if supported */
		drba->drba_snapobj = dp->dp_origin_snap != NULL ?
		    dp->dp_origin_snap->ds_object : 0;
	}

	return (0);

}