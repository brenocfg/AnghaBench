#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct osm_routing_engine {scalar_t__ (* mcast_build_stree ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  context; } ;
struct TYPE_8__ {int /*<<< orphan*/  p_log; TYPE_3__* p_subn; } ;
typedef  TYPE_2__ osm_sm_t ;
typedef  int /*<<< orphan*/  osm_mgrp_box_t ;
typedef  scalar_t__ ib_api_status_t ;
struct TYPE_9__ {TYPE_1__* p_osm; } ;
struct TYPE_7__ {struct osm_routing_engine* routing_engine_used; } ;

/* Variables and functions */
 scalar_t__ IB_SUCCESS ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  OSM_LOG_DEBUG ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_hton16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_get_err_str (scalar_t__) ; 
 scalar_t__ mcast_mgr_build_spanning_tree (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcast_mgr_clear (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * osm_get_mbox_by_mlid (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ib_api_status_t mcast_mgr_process_mlid(osm_sm_t * sm, uint16_t mlid)
{
	ib_api_status_t status = IB_SUCCESS;
	struct osm_routing_engine *re = sm->p_subn->p_osm->routing_engine_used;
	osm_mgrp_box_t *mbox;

	OSM_LOG_ENTER(sm->p_log);

	OSM_LOG(sm->p_log, OSM_LOG_DEBUG,
		"Processing multicast group with mlid 0x%X\n", mlid);

	/* Clear the multicast tables to start clean, then build
	   the spanning tree which sets the mcast table bits for each
	   port in the group. */
	mcast_mgr_clear(sm, mlid);

	mbox = osm_get_mbox_by_mlid(sm->p_subn, cl_hton16(mlid));
	if (mbox) {
		if (re && re->mcast_build_stree)
			status = re->mcast_build_stree(re->context, mbox);
		else
			status = mcast_mgr_build_spanning_tree(sm, mbox);

		if (status != IB_SUCCESS)
			OSM_LOG(sm->p_log, OSM_LOG_ERROR, "ERR 0A17: "
				"Unable to create spanning tree (%s) for mlid "
				"0x%x\n", ib_get_err_str(status), mlid);
	}

	OSM_LOG_EXIT(sm->p_log);
	return status;
}