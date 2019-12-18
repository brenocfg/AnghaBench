#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_5__ {int /*<<< orphan*/  db_size; int /*<<< orphan*/  db_data; } ;
struct TYPE_6__ {scalar_t__ db_state; scalar_t__ db_level; scalar_t__ db_blkid; int /*<<< orphan*/  db_mtx; int /*<<< orphan*/  db_changed; scalar_t__ db_freed_in_flight; TYPE_1__ db; } ;
typedef  TYPE_2__ dmu_buf_impl_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DBUF_VERIFY (TYPE_2__*) ; 
 scalar_t__ DB_CACHED ; 
 scalar_t__ DB_FILL ; 
 scalar_t__ DMU_BONUS_BLKID ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
dbuf_fill_done(dmu_buf_impl_t *db, dmu_tx_t *tx)
{
	mutex_enter(&db->db_mtx);
	DBUF_VERIFY(db);

	if (db->db_state == DB_FILL) {
		if (db->db_level == 0 && db->db_freed_in_flight) {
			ASSERT(db->db_blkid != DMU_BONUS_BLKID);
			/* we were freed while filling */
			/* XXX dbuf_undirty? */
			bzero(db->db.db_data, db->db.db_size);
			db->db_freed_in_flight = FALSE;
		}
		db->db_state = DB_CACHED;
		cv_broadcast(&db->db_changed);
	}
	mutex_exit(&db->db_mtx);
}