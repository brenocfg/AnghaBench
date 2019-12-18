#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* p_event_wheel; } ;
struct TYPE_10__ {void* is_closing; TYPE_3__ txn_mgr; TYPE_1__* p_vendor; } ;
typedef  TYPE_4__ osmv_bind_obj_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
typedef  scalar_t__ osm_bind_handle_t ;
struct TYPE_8__ {void* closing; } ;
struct TYPE_7__ {int /*<<< orphan*/ * p_log; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG_DEBUG ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ *) ; 
 void* TRUE ; 
 int /*<<< orphan*/  osm_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  osmv_transport_done (scalar_t__) ; 
 int /*<<< orphan*/  osmv_txn_abort_rmpp_txns (scalar_t__) ; 
 int /*<<< orphan*/  osmv_txn_lock (TYPE_4__*) ; 
 int /*<<< orphan*/  osmv_txn_unlock (TYPE_4__*) ; 
 int /*<<< orphan*/  osmv_txnmgr_done (scalar_t__) ; 

__attribute__((used)) static void __osm_vendor_internal_unbind(osm_bind_handle_t h_bind)
{
	osmv_bind_obj_t *p_bo = (osmv_bind_obj_t *) h_bind;
	osm_log_t *p_log = p_bo->p_vendor->p_log;

	OSM_LOG_ENTER(p_log);

	/* "notifying" all that from now on no new sends can be done */
	p_bo->txn_mgr.p_event_wheel->closing = TRUE;

	osmv_txn_lock(p_bo);
	p_bo->is_closing = TRUE;

	/* notifying all sleeping rmpp sends to exit */
	osmv_txn_abort_rmpp_txns(h_bind);

	/*  frees all data in bind handle   */
	osm_log(p_log, OSM_LOG_DEBUG,
		"__osm_vendor_internal_unbind: destroying transport mgr.. \n");
	osmv_txn_unlock(p_bo);

	osmv_transport_done(h_bind);
	osm_log(p_log, OSM_LOG_DEBUG,
		"__osm_vendor_internal_unbind: destroying txn mgr.. \n");
	osmv_txn_lock(p_bo);
	osmv_txnmgr_done(h_bind);
	osm_log(p_log, OSM_LOG_DEBUG,
		"__osm_vendor_internal_unbind: destroying bind lock.. \n");

	osmv_txn_unlock(p_bo);
	/*
	   we intentionally let the p_bo and its lock leak -
	   as we did not implement a way to track active bind handles provided to
	   the client - and the client might use them

	   cl_spinlock_destroy(&p_bo->lock);
	   free(p_bo);
	 */

	OSM_LOG_EXIT(p_log);
}