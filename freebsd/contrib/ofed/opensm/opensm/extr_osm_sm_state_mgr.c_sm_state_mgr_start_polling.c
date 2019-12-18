#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  p_log; int /*<<< orphan*/  polling_timer; int /*<<< orphan*/  p_lock; TYPE_2__* p_subn; scalar_t__ retry_number; } ;
typedef  TYPE_3__ osm_sm_t ;
typedef  scalar_t__ cl_status_t ;
struct TYPE_6__ {int /*<<< orphan*/  sminfo_polling_timeout; } ;
struct TYPE_7__ {int /*<<< orphan*/  sm_state; TYPE_1__ opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_PLOCK_ACQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_PLOCK_RELEASE (int /*<<< orphan*/ ) ; 
 scalar_t__ CL_SUCCESS ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ ) ; 
 scalar_t__ cl_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm_state_mgr_send_master_sm_info_req (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sm_state_mgr_start_polling(osm_sm_t * sm)
{
	uint32_t timeout;
	cl_status_t cl_status;

	OSM_LOG_ENTER(sm->p_log);

	/*
	 * Init the retry_number back to zero - need to restart counting
	 */
	sm->retry_number = 0;

	/*
	 * Send a SubnGet(SMInfo) query to the current (or new) master found.
	 */
	CL_PLOCK_ACQUIRE(sm->p_lock);
	timeout = sm->p_subn->opt.sminfo_polling_timeout;
	sm_state_mgr_send_master_sm_info_req(sm, sm->p_subn->sm_state);
	CL_PLOCK_RELEASE(sm->p_lock);

	/*
	 * Start a timer that will wake up every sminfo_polling_timeout milliseconds.
	 * The callback of the timer will send a SubnGet(SMInfo) to the Master SM
	 * and restart the timer
	 */
	cl_status = cl_timer_start(&sm->polling_timer, timeout);
	if (cl_status != CL_SUCCESS)
		OSM_LOG(sm->p_log, OSM_LOG_ERROR, "ERR 3210: "
			"Failed to start polling timer\n");

	OSM_LOG_EXIT(sm->p_log);
}