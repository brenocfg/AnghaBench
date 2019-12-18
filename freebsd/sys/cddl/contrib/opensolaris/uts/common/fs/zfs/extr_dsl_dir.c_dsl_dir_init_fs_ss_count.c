#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_20__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_15__ ;

/* Type definitions */
struct TYPE_23__ {char* za_name; int /*<<< orphan*/  za_first_integer; } ;
typedef  TYPE_1__ zap_cursor_t ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  my_ss_cnt ;
typedef  int /*<<< orphan*/  my_fs_cnt ;
struct TYPE_25__ {int /*<<< orphan*/  dp_spa; int /*<<< orphan*/ * dp_meta_objset; } ;
typedef  TYPE_3__ dsl_pool_t ;
struct TYPE_26__ {char* dd_myname; int /*<<< orphan*/  dd_object; int /*<<< orphan*/  dd_dbuf; TYPE_3__* dd_pool; } ;
typedef  TYPE_4__ dsl_dir_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  count ;
struct TYPE_24__ {int /*<<< orphan*/  ds_snapnames_zapobj; } ;
struct TYPE_22__ {int /*<<< orphan*/  dd_head_dataset_obj; int /*<<< orphan*/  dd_child_dir_zapobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DD_FIELD_FILESYSTEM_COUNT ; 
 int /*<<< orphan*/  DD_FIELD_SNAPSHOT_COUNT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  SPA_FEATURE_FS_SS_LIMIT ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_is_syncing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_hold_obj (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 TYPE_20__* dsl_dataset_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dir_hold_obj (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__**) ; 
 TYPE_15__* dsl_dir_phys (TYPE_4__*) ; 
 int /*<<< orphan*/  dsl_dir_rele (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dir_zapify (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_config_held (TYPE_3__*) ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spa_feature_is_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zap_contains (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_cursor_advance (TYPE_1__*) ; 
 int /*<<< orphan*/  zap_cursor_fini (TYPE_1__*) ; 
 int /*<<< orphan*/  zap_cursor_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zap_cursor_retrieve (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 

__attribute__((used)) static void
dsl_dir_init_fs_ss_count(dsl_dir_t *dd, dmu_tx_t *tx)
{
	uint64_t my_fs_cnt = 0;
	uint64_t my_ss_cnt = 0;
	dsl_pool_t *dp = dd->dd_pool;
	objset_t *os = dp->dp_meta_objset;
	zap_cursor_t *zc;
	zap_attribute_t *za;
	dsl_dataset_t *ds;

	ASSERT(spa_feature_is_active(dp->dp_spa, SPA_FEATURE_FS_SS_LIMIT));
	ASSERT(dsl_pool_config_held(dp));
	ASSERT(dmu_tx_is_syncing(tx));

	dsl_dir_zapify(dd, tx);

	/*
	 * If the filesystem count has already been initialized then we
	 * don't need to recurse down any further.
	 */
	if (zap_contains(os, dd->dd_object, DD_FIELD_FILESYSTEM_COUNT) == 0)
		return;

	zc = kmem_alloc(sizeof (zap_cursor_t), KM_SLEEP);
	za = kmem_alloc(sizeof (zap_attribute_t), KM_SLEEP);

	/* Iterate my child dirs */
	for (zap_cursor_init(zc, os, dsl_dir_phys(dd)->dd_child_dir_zapobj);
	    zap_cursor_retrieve(zc, za) == 0; zap_cursor_advance(zc)) {
		dsl_dir_t *chld_dd;
		uint64_t count;

		VERIFY0(dsl_dir_hold_obj(dp, za->za_first_integer, NULL, FTAG,
		    &chld_dd));

		/*
		 * Ignore hidden ($FREE, $MOS & $ORIGIN) objsets and
		 * temporary datasets.
		 */
		if (chld_dd->dd_myname[0] == '$' ||
		    chld_dd->dd_myname[0] == '%') {
			dsl_dir_rele(chld_dd, FTAG);
			continue;
		}

		my_fs_cnt++;	/* count this child */

		dsl_dir_init_fs_ss_count(chld_dd, tx);

		VERIFY0(zap_lookup(os, chld_dd->dd_object,
		    DD_FIELD_FILESYSTEM_COUNT, sizeof (count), 1, &count));
		my_fs_cnt += count;
		VERIFY0(zap_lookup(os, chld_dd->dd_object,
		    DD_FIELD_SNAPSHOT_COUNT, sizeof (count), 1, &count));
		my_ss_cnt += count;

		dsl_dir_rele(chld_dd, FTAG);
	}
	zap_cursor_fini(zc);
	/* Count my snapshots (we counted children's snapshots above) */
	VERIFY0(dsl_dataset_hold_obj(dd->dd_pool,
	    dsl_dir_phys(dd)->dd_head_dataset_obj, FTAG, &ds));

	for (zap_cursor_init(zc, os, dsl_dataset_phys(ds)->ds_snapnames_zapobj);
	    zap_cursor_retrieve(zc, za) == 0;
	    zap_cursor_advance(zc)) {
		/* Don't count temporary snapshots */
		if (za->za_name[0] != '%')
			my_ss_cnt++;
	}
	zap_cursor_fini(zc);

	dsl_dataset_rele(ds, FTAG);

	kmem_free(zc, sizeof (zap_cursor_t));
	kmem_free(za, sizeof (zap_attribute_t));

	/* we're in a sync task, update counts */
	dmu_buf_will_dirty(dd->dd_dbuf, tx);
	VERIFY0(zap_add(os, dd->dd_object, DD_FIELD_FILESYSTEM_COUNT,
	    sizeof (my_fs_cnt), 1, &my_fs_cnt, tx));
	VERIFY0(zap_add(os, dd->dd_object, DD_FIELD_SNAPSHOT_COUNT,
	    sizeof (my_ss_cnt), 1, &my_ss_cnt, tx));
}