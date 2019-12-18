#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dbu_tqent; int /*<<< orphan*/ * dbu_evict_func_async; int /*<<< orphan*/  (* dbu_evict_func_sync ) (TYPE_1__*) ;int /*<<< orphan*/ ** dbu_clear_on_evict_dbufp; } ;
typedef  TYPE_1__ dmu_buf_user_t ;
struct TYPE_8__ {TYPE_1__* db_user; int /*<<< orphan*/  db_mtx; } ;
typedef  TYPE_2__ dmu_buf_impl_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBVU_EVICTING ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbu_evict_taskq ; 
 int /*<<< orphan*/  dbuf_verify_user (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  taskq_dispatch_ent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dbuf_evict_user(dmu_buf_impl_t *db)
{
	dmu_buf_user_t *dbu = db->db_user;

	ASSERT(MUTEX_HELD(&db->db_mtx));

	if (dbu == NULL)
		return;

	dbuf_verify_user(db, DBVU_EVICTING);
	db->db_user = NULL;

#ifdef ZFS_DEBUG
	if (dbu->dbu_clear_on_evict_dbufp != NULL)
		*dbu->dbu_clear_on_evict_dbufp = NULL;
#endif

	/*
	 * There are two eviction callbacks - one that we call synchronously
	 * and one that we invoke via a taskq.  The async one is useful for
	 * avoiding lock order reversals and limiting stack depth.
	 *
	 * Note that if we have a sync callback but no async callback,
	 * it's likely that the sync callback will free the structure
	 * containing the dbu.  In that case we need to take care to not
	 * dereference dbu after calling the sync evict func.
	 */
	boolean_t has_async = (dbu->dbu_evict_func_async != NULL);

	if (dbu->dbu_evict_func_sync != NULL)
		dbu->dbu_evict_func_sync(dbu);

	if (has_async) {
		taskq_dispatch_ent(dbu_evict_taskq, dbu->dbu_evict_func_async,
		    dbu, 0, &dbu->dbu_tqent);
	}
}