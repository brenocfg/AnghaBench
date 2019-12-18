#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ss_cnt ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  fs_cnt ;
struct TYPE_23__ {int /*<<< orphan*/  dp_spa; int /*<<< orphan*/ * dp_meta_objset; } ;
typedef  TYPE_2__ dsl_pool_t ;
struct TYPE_24__ {int /*<<< orphan*/  dd_object; int /*<<< orphan*/  dd_myname; struct TYPE_24__* dd_parent; int /*<<< orphan*/  dd_dbuf; TYPE_1__* dd_pool; } ;
typedef  TYPE_3__ dsl_dir_t ;
struct TYPE_25__ {int /*<<< orphan*/  ddra_newname; int /*<<< orphan*/  ddra_oldname; } ;
typedef  TYPE_4__ dsl_dir_rename_arg_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_22__ {int /*<<< orphan*/ * dp_meta_objset; } ;
struct TYPE_21__ {int /*<<< orphan*/  dd_child_dir_zapobj; int /*<<< orphan*/  dd_parent_obj; int /*<<< orphan*/  dd_used_bytes; int /*<<< orphan*/  dd_reserved; int /*<<< orphan*/  dd_uncompressed_bytes; int /*<<< orphan*/  dd_compressed_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int) ; 
 int /*<<< orphan*/  DD_FIELD_FILESYSTEM_COUNT ; 
 int /*<<< orphan*/  DD_FIELD_SNAPSHOT_COUNT ; 
 int /*<<< orphan*/  DD_USED_CHILD ; 
 int /*<<< orphan*/  DD_USED_CHILD_RSRV ; 
 TYPE_3__* FTAG ; 
 int /*<<< orphan*/  SPA_FEATURE_FS_SS_LIMIT ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_diduse_space (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_hold (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__**,char const**) ; 
 int /*<<< orphan*/  dsl_dir_hold_obj (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__**) ; 
 TYPE_10__* dsl_dir_phys (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_dir_rele (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_fs_ss_count_adjust (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_prop_notify_all (TYPE_3__*) ; 
 scalar_t__ spa_feature_is_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_history_log_internal_dd (TYPE_3__*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  zap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int zap_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfsvfs_update_fromname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_rename_minors (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dsl_dir_rename_sync(void *arg, dmu_tx_t *tx)
{
	dsl_dir_rename_arg_t *ddra = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dir_t *dd, *newparent;
	const char *mynewname;
	int error;
	objset_t *mos = dp->dp_meta_objset;

	VERIFY0(dsl_dir_hold(dp, ddra->ddra_oldname, FTAG, &dd, NULL));
	VERIFY0(dsl_dir_hold(dp, ddra->ddra_newname, FTAG, &newparent,
	    &mynewname));

	/* Log this before we change the name. */
	spa_history_log_internal_dd(dd, "rename", tx,
	    "-> %s", ddra->ddra_newname);

	if (newparent != dd->dd_parent) {
		objset_t *os = dd->dd_pool->dp_meta_objset;
		uint64_t fs_cnt = 0;
		uint64_t ss_cnt = 0;

		/*
		 * We already made sure the dd counts were initialized in the
		 * check function.
		 */
		if (spa_feature_is_active(dp->dp_spa,
		    SPA_FEATURE_FS_SS_LIMIT)) {
			VERIFY0(zap_lookup(os, dd->dd_object,
			    DD_FIELD_FILESYSTEM_COUNT, sizeof (fs_cnt), 1,
			    &fs_cnt));
			/* add 1 for the filesystem itself that we're moving */
			fs_cnt++;

			VERIFY0(zap_lookup(os, dd->dd_object,
			    DD_FIELD_SNAPSHOT_COUNT, sizeof (ss_cnt), 1,
			    &ss_cnt));
		}

		dsl_fs_ss_count_adjust(dd->dd_parent, -fs_cnt,
		    DD_FIELD_FILESYSTEM_COUNT, tx);
		dsl_fs_ss_count_adjust(newparent, fs_cnt,
		    DD_FIELD_FILESYSTEM_COUNT, tx);

		dsl_fs_ss_count_adjust(dd->dd_parent, -ss_cnt,
		    DD_FIELD_SNAPSHOT_COUNT, tx);
		dsl_fs_ss_count_adjust(newparent, ss_cnt,
		    DD_FIELD_SNAPSHOT_COUNT, tx);

		dsl_dir_diduse_space(dd->dd_parent, DD_USED_CHILD,
		    -dsl_dir_phys(dd)->dd_used_bytes,
		    -dsl_dir_phys(dd)->dd_compressed_bytes,
		    -dsl_dir_phys(dd)->dd_uncompressed_bytes, tx);
		dsl_dir_diduse_space(newparent, DD_USED_CHILD,
		    dsl_dir_phys(dd)->dd_used_bytes,
		    dsl_dir_phys(dd)->dd_compressed_bytes,
		    dsl_dir_phys(dd)->dd_uncompressed_bytes, tx);

		if (dsl_dir_phys(dd)->dd_reserved >
		    dsl_dir_phys(dd)->dd_used_bytes) {
			uint64_t unused_rsrv = dsl_dir_phys(dd)->dd_reserved -
			    dsl_dir_phys(dd)->dd_used_bytes;

			dsl_dir_diduse_space(dd->dd_parent, DD_USED_CHILD_RSRV,
			    -unused_rsrv, 0, 0, tx);
			dsl_dir_diduse_space(newparent, DD_USED_CHILD_RSRV,
			    unused_rsrv, 0, 0, tx);
		}
	}

	dmu_buf_will_dirty(dd->dd_dbuf, tx);

	/* remove from old parent zapobj */
	error = zap_remove(mos,
	    dsl_dir_phys(dd->dd_parent)->dd_child_dir_zapobj,
	    dd->dd_myname, tx);
	ASSERT0(error);

	(void) strcpy(dd->dd_myname, mynewname);
	dsl_dir_rele(dd->dd_parent, dd);
	dsl_dir_phys(dd)->dd_parent_obj = newparent->dd_object;
	VERIFY0(dsl_dir_hold_obj(dp,
	    newparent->dd_object, NULL, dd, &dd->dd_parent));

	/* add to new parent zapobj */
	VERIFY0(zap_add(mos, dsl_dir_phys(newparent)->dd_child_dir_zapobj,
	    dd->dd_myname, 8, 1, &dd->dd_object, tx));

#ifdef __FreeBSD__
#ifdef _KERNEL
	zfsvfs_update_fromname(ddra->ddra_oldname, ddra->ddra_newname);
	zvol_rename_minors(ddra->ddra_oldname, ddra->ddra_newname);
#endif
#endif

	dsl_prop_notify_all(dd);

	dsl_dir_rele(newparent, FTAG);
	dsl_dir_rele(dd, FTAG);
}