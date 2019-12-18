#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {int /*<<< orphan*/  is_mc_member; int /*<<< orphan*/  p_node; } ;
typedef  TYPE_1__ osm_switch_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_log; } ;
typedef  TYPE_2__ osm_sm_t ;
typedef  int /*<<< orphan*/  cl_qmap_t ;
typedef  int /*<<< orphan*/  cl_map_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ ) ; 
 TYPE_1__* cl_item_obj (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_ntoh16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_qmap_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgrp_item ; 
 int /*<<< orphan*/  osm_node_get_base_lid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ osm_switch_get_least_hops (TYPE_1__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static float mcast_mgr_compute_max_hops(osm_sm_t * sm, cl_qmap_t * m,
					const osm_switch_t * this_sw)
{
	uint32_t max_hops = 0, hops;
	uint16_t lid;
	cl_map_item_t *i;
	osm_switch_t *sw;

	OSM_LOG_ENTER(sm->p_log);

	/*
	   For each member of the multicast group, compute the
	   number of hops to its base LID.
	 */
	for (i = cl_qmap_head(m); i != cl_qmap_end(m); i = cl_qmap_next(i)) {
		sw = cl_item_obj(i, sw, mgrp_item);
		lid = cl_ntoh16(osm_node_get_base_lid(sw->p_node, 0));
		hops = osm_switch_get_least_hops(this_sw, lid);
		if (!sw->is_mc_member)
			hops += 1;
		if (hops > max_hops)
			max_hops = hops;
	}

	/* Note that at this point we might get (max_hops == 0),
	   which means that there's only one member in the mcast
	   group, and it's the current switch */

	OSM_LOG_EXIT(sm->p_log);
	return (float)max_hops;
}