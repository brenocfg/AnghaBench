#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {int /*<<< orphan*/  os_flags; } ;
typedef  TYPE_1__ objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FORREAL ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  JUSTLOOKING ; 
 int /*<<< orphan*/  OBJSET_FLAG_USERACCOUNTING_COMPLETE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int dmu_bonus_hold (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_buf_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dmu_object_next (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dmu_objset_is_snapshot (TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_objset_pool (TYPE_1__*) ; 
 scalar_t__ dmu_objset_userspace_present (TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_objset_userused_enabled (TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_tx_hold_bonus (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ issig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
dmu_objset_userspace_upgrade(objset_t *os)
{
	uint64_t obj;
	int err = 0;

	if (dmu_objset_userspace_present(os))
		return (0);
	if (!dmu_objset_userused_enabled(os))
		return (SET_ERROR(ENOTSUP));
	if (dmu_objset_is_snapshot(os))
		return (SET_ERROR(EINVAL));

	/*
	 * We simply need to mark every object dirty, so that it will be
	 * synced out and now accounted.  If this is called
	 * concurrently, or if we already did some work before crashing,
	 * that's fine, since we track each object's accounted state
	 * independently.
	 */

	for (obj = 0; err == 0; err = dmu_object_next(os, &obj, FALSE, 0)) {
		dmu_tx_t *tx;
		dmu_buf_t *db;
		int objerr;

		if (issig(JUSTLOOKING) && issig(FORREAL))
			return (SET_ERROR(EINTR));

		objerr = dmu_bonus_hold(os, obj, FTAG, &db);
		if (objerr != 0)
			continue;
		tx = dmu_tx_create(os);
		dmu_tx_hold_bonus(tx, obj);
		objerr = dmu_tx_assign(tx, TXG_WAIT);
		if (objerr != 0) {
			dmu_tx_abort(tx);
			continue;
		}
		dmu_buf_will_dirty(db, tx);
		dmu_buf_rele(db, FTAG);
		dmu_tx_commit(tx);
	}

	os->os_flags |= OBJSET_FLAG_USERACCOUNTING_COMPLETE;
	txg_wait_synced(dmu_objset_pool(os), 0);
	return (0);
}