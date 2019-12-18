#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  congestion_control; } ;
struct TYPE_5__ {int /*<<< orphan*/  port_guid_tbl; TYPE_1__ opt; } ;
struct osm_opensm {int /*<<< orphan*/  log; int /*<<< orphan*/  lock; int /*<<< orphan*/  sm; TYPE_2__ subn; int /*<<< orphan*/  routing_engine_used; } ;
struct TYPE_6__ {int /*<<< orphan*/  p_physp; scalar_t__ cc_unavailable_flag; int /*<<< orphan*/ * p_node; } ;
typedef  TYPE_3__ osm_port_t ;
typedef  int /*<<< orphan*/  osm_node_t ;
typedef  scalar_t__ ib_api_status_t ;
typedef  int /*<<< orphan*/  cl_qmap_t ;
typedef  int /*<<< orphan*/  cl_map_item_t ;

/* Variables and functions */
 scalar_t__ IB_NODE_TYPE_CA ; 
 scalar_t__ IB_NODE_TYPE_SWITCH ; 
 scalar_t__ IB_SUCCESS ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ *) ; 
 scalar_t__ cc_send_ca_cong_setting (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cc_send_cct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cc_send_sw_cong_setting (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cc_setup_mad_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_plock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_plock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_next (int /*<<< orphan*/ *) ; 
 scalar_t__ osm_node_get_type (int /*<<< orphan*/ *) ; 

int osm_congestion_control_setup(struct osm_opensm *p_osm)
{
	cl_qmap_t *p_tbl;
	cl_map_item_t *p_next;
	int ret = 0;

	if (!p_osm->subn.opt.congestion_control)
		return 0;

	OSM_LOG_ENTER(&p_osm->log);

	/*
	 * Do nothing unless the most recent routing attempt was successful.
	 */
	if (!p_osm->routing_engine_used)
		return 0;

	cc_setup_mad_data(&p_osm->sm);

	cl_plock_acquire(&p_osm->lock);

	p_tbl = &p_osm->subn.port_guid_tbl;
	p_next = cl_qmap_head(p_tbl);
	while (p_next != cl_qmap_end(p_tbl)) {
		osm_port_t *p_port = (osm_port_t *) p_next;
		osm_node_t *p_node = p_port->p_node;
		ib_api_status_t status;

		p_next = cl_qmap_next(p_next);

		if (p_port->cc_unavailable_flag)
			continue;

		if (osm_node_get_type(p_node) == IB_NODE_TYPE_SWITCH) {
			status = cc_send_sw_cong_setting(&p_osm->sm, p_node);
			if (status != IB_SUCCESS)
				ret = -1;
		} else if (osm_node_get_type(p_node) == IB_NODE_TYPE_CA) {
			status = cc_send_ca_cong_setting(&p_osm->sm,
							 p_node,
							 p_port->p_physp);
			if (status != IB_SUCCESS)
				ret = -1;

			status = cc_send_cct(&p_osm->sm,
					     p_node,
					     p_port->p_physp);
			if (status != IB_SUCCESS)
				ret = -1;
		}
	}

	cl_plock_release(&p_osm->lock);

	OSM_LOG_EXIT(&p_osm->log);

	return ret;
}