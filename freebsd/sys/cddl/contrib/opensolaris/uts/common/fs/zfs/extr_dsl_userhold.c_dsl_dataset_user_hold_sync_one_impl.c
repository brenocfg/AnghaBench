#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ minor_t ;
struct TYPE_10__ {int /*<<< orphan*/  dp_config_rwlock; int /*<<< orphan*/ * dp_meta_objset; } ;
typedef  TYPE_2__ dsl_pool_t ;
struct TYPE_11__ {int /*<<< orphan*/  ds_userrefs; scalar_t__ ds_object; int /*<<< orphan*/  ds_dbuf; TYPE_1__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_12__ {scalar_t__ ds_userrefs_obj; } ;
struct TYPE_9__ {TYPE_2__* dd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 int /*<<< orphan*/  DMU_OT_USERREFS ; 
 int MAXNAMELEN ; 
 int /*<<< orphan*/  RRW_WRITE_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_7__* dsl_dataset_phys (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_pool_user_hold (TYPE_2__*,scalar_t__,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_history_log_internal_ds (TYPE_3__*,char*,int /*<<< orphan*/ *,char*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_add (int /*<<< orphan*/ *,scalar_t__,char const*,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zap_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_dataset_user_hold_sync_one_impl(nvlist_t *tmpholds, dsl_dataset_t *ds,
    const char *htag, minor_t minor, uint64_t now, dmu_tx_t *tx)
{
	dsl_pool_t *dp = ds->ds_dir->dd_pool;
	objset_t *mos = dp->dp_meta_objset;
	uint64_t zapobj;

	ASSERT(RRW_WRITE_HELD(&dp->dp_config_rwlock));

	if (dsl_dataset_phys(ds)->ds_userrefs_obj == 0) {
		/*
		 * This is the first user hold for this dataset.  Create
		 * the userrefs zap object.
		 */
		dmu_buf_will_dirty(ds->ds_dbuf, tx);
		zapobj = dsl_dataset_phys(ds)->ds_userrefs_obj =
		    zap_create(mos, DMU_OT_USERREFS, DMU_OT_NONE, 0, tx);
	} else {
		zapobj = dsl_dataset_phys(ds)->ds_userrefs_obj;
	}
	ds->ds_userrefs++;

	VERIFY0(zap_add(mos, zapobj, htag, 8, 1, &now, tx));

	if (minor != 0) {
		char name[MAXNAMELEN];
		nvlist_t *tags;

		VERIFY0(dsl_pool_user_hold(dp, ds->ds_object,
		    htag, now, tx));
		(void) snprintf(name, sizeof (name), "%llx",
		    (u_longlong_t)ds->ds_object);

		if (nvlist_lookup_nvlist(tmpholds, name, &tags) != 0) {
			tags = fnvlist_alloc();
			fnvlist_add_boolean(tags, htag);
			fnvlist_add_nvlist(tmpholds, name, tags);
			fnvlist_free(tags);
		} else {
			fnvlist_add_boolean(tags, htag);
		}
	}

	spa_history_log_internal_ds(ds, "hold", tx,
	    "tag=%s temp=%d refs=%llu",
	    htag, minor != 0, ds->ds_userrefs);
}