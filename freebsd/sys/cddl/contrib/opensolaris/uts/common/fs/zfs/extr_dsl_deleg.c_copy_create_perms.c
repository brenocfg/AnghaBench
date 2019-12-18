#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_9__ {int za_integer_length; int za_num_integers; int /*<<< orphan*/  za_name; } ;
typedef  TYPE_2__ zap_attribute_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_10__ {int /*<<< orphan*/  dd_dbuf; TYPE_1__* dd_pool; } ;
typedef  TYPE_3__ dsl_dir_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_11__ {scalar_t__ dd_deleg_zapobj; } ;
struct TYPE_8__ {int /*<<< orphan*/ * dp_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DMU_OT_DSL_PERMS ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZFS_DELEG_CREATE ; 
 int /*<<< orphan*/  ZFS_DELEG_CREATE_SETS ; 
 int /*<<< orphan*/  ZFS_DELEG_LOCAL ; 
 int /*<<< orphan*/  ZFS_DELEG_USER ; 
 int /*<<< orphan*/  ZFS_DELEG_USER_SETS ; 
 int ZFS_MAX_DELEG_NAME ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__* dsl_dir_phys (TYPE_3__*) ; 
 scalar_t__ zap_add (int /*<<< orphan*/ *,scalar_t__,char*,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 void* zap_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ zap_lookup (int /*<<< orphan*/ *,scalar_t__,char*,int,int,scalar_t__*) ; 
 scalar_t__ zap_update (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_deleg_whokey (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void
copy_create_perms(dsl_dir_t *dd, uint64_t pzapobj,
    boolean_t dosets, uint64_t uid, dmu_tx_t *tx)
{
	objset_t *mos = dd->dd_pool->dp_meta_objset;
	uint64_t jumpobj, pjumpobj;
	uint64_t zapobj = dsl_dir_phys(dd)->dd_deleg_zapobj;
	zap_cursor_t zc;
	zap_attribute_t za;
	char whokey[ZFS_MAX_DELEG_NAME];

	zfs_deleg_whokey(whokey,
	    dosets ? ZFS_DELEG_CREATE_SETS : ZFS_DELEG_CREATE,
	    ZFS_DELEG_LOCAL, NULL);
	if (zap_lookup(mos, pzapobj, whokey, 8, 1, &pjumpobj) != 0)
		return;

	if (zapobj == 0) {
		dmu_buf_will_dirty(dd->dd_dbuf, tx);
		zapobj = dsl_dir_phys(dd)->dd_deleg_zapobj = zap_create(mos,
		    DMU_OT_DSL_PERMS, DMU_OT_NONE, 0, tx);
	}

	zfs_deleg_whokey(whokey,
	    dosets ? ZFS_DELEG_USER_SETS : ZFS_DELEG_USER,
	    ZFS_DELEG_LOCAL, &uid);
	if (zap_lookup(mos, zapobj, whokey, 8, 1, &jumpobj) == ENOENT) {
		jumpobj = zap_create(mos, DMU_OT_DSL_PERMS, DMU_OT_NONE, 0, tx);
		VERIFY(zap_add(mos, zapobj, whokey, 8, 1, &jumpobj, tx) == 0);
	}

	for (zap_cursor_init(&zc, mos, pjumpobj);
	    zap_cursor_retrieve(&zc, &za) == 0;
	    zap_cursor_advance(&zc)) {
		uint64_t zero = 0;
		ASSERT(za.za_integer_length == 8 && za.za_num_integers == 1);

		VERIFY(zap_update(mos, jumpobj, za.za_name,
		    8, 1, &zero, tx) == 0);
	}
	zap_cursor_fini(&zc);
}