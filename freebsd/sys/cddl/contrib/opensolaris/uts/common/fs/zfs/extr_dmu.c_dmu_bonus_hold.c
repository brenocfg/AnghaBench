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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_9__ {int /*<<< orphan*/  dn_struct_rwlock; int /*<<< orphan*/  dn_dbufs_count; TYPE_2__* dn_bonus; } ;
typedef  TYPE_1__ dnode_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;
struct TYPE_10__ {int /*<<< orphan*/  db; int /*<<< orphan*/  db_holds; } ;
typedef  TYPE_2__ dmu_buf_impl_t ;

/* Variables and functions */
 int DB_RF_MUST_SUCCEED ; 
 int DB_RF_NOPREFETCH ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  atomic_inc_32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbuf_create_bonus (TYPE_1__*) ; 
 scalar_t__ dbuf_read (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int dnode_add_ref (TYPE_1__*,TYPE_2__*) ; 
 int dnode_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  dnode_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int zfs_refcount_add (int /*<<< orphan*/ *,void*) ; 

int
dmu_bonus_hold(objset_t *os, uint64_t object, void *tag, dmu_buf_t **dbp)
{
	dnode_t *dn;
	dmu_buf_impl_t *db;
	int error;

	error = dnode_hold(os, object, FTAG, &dn);
	if (error)
		return (error);

	rw_enter(&dn->dn_struct_rwlock, RW_READER);
	if (dn->dn_bonus == NULL) {
		rw_exit(&dn->dn_struct_rwlock);
		rw_enter(&dn->dn_struct_rwlock, RW_WRITER);
		if (dn->dn_bonus == NULL)
			dbuf_create_bonus(dn);
	}
	db = dn->dn_bonus;

	/* as long as the bonus buf is held, the dnode will be held */
	if (zfs_refcount_add(&db->db_holds, tag) == 1) {
		VERIFY(dnode_add_ref(dn, db));
		atomic_inc_32(&dn->dn_dbufs_count);
	}

	/*
	 * Wait to drop dn_struct_rwlock until after adding the bonus dbuf's
	 * hold and incrementing the dbuf count to ensure that dnode_move() sees
	 * a dnode hold for every dbuf.
	 */
	rw_exit(&dn->dn_struct_rwlock);

	dnode_rele(dn, FTAG);

	VERIFY(0 == dbuf_read(db, NULL, DB_RF_MUST_SUCCEED | DB_RF_NOPREFETCH));

	*dbp = &db->db;
	return (0);
}