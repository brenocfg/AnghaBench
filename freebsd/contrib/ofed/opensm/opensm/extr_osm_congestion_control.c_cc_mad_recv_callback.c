#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osm_madw_t ;
struct TYPE_2__ {int /*<<< orphan*/  log; int /*<<< orphan*/  mad_pool; int /*<<< orphan*/  cc_disp_h; } ;
typedef  TYPE_1__ osm_congestion_control_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (int /*<<< orphan*/ *) ; 
 scalar_t__ CL_SUCCESS ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_MSG_MAD_CC ; 
 scalar_t__ cl_disp_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_mad_pool_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_madw_copy_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cc_mad_recv_callback(osm_madw_t * p_madw, void *bind_context,
				 osm_madw_t * p_req_madw)
{
	osm_congestion_control_t *p_cc = bind_context;

	OSM_LOG_ENTER(p_cc->log);

	CL_ASSERT(p_madw);

	/* HACK - should be extended when supporting CC traps */
	CL_ASSERT(p_req_madw != NULL);

	osm_madw_copy_context(p_madw, p_req_madw);
	osm_mad_pool_put(p_cc->mad_pool, p_req_madw);

	/* Do not decrement outstanding mads here, do it in the dispatcher */

	if (cl_disp_post(p_cc->cc_disp_h, OSM_MSG_MAD_CC,
			 p_madw, NULL, NULL) != CL_SUCCESS) {
		OSM_LOG(p_cc->log, OSM_LOG_ERROR, "ERR C105: "
			"Congestion Control Dispatcher post failed\n");
		osm_mad_pool_put(p_cc->mad_pool, p_madw);
	}

	OSM_LOG_EXIT(p_cc->log);
}