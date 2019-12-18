#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  switch_t ;
struct TYPE_13__ {int /*<<< orphan*/  p_node; int /*<<< orphan*/  map_item; } ;
typedef  TYPE_3__ osm_switch_t ;
struct TYPE_11__ {scalar_t__ lash_start_vl; } ;
struct TYPE_14__ {TYPE_1__ opt; int /*<<< orphan*/  sw_guid_tbl; } ;
typedef  TYPE_4__ osm_subn_t ;
struct TYPE_15__ {int /*<<< orphan*/  port_info; scalar_t__ p_remote_physp; } ;
typedef  TYPE_5__ osm_physp_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
struct TYPE_16__ {int /*<<< orphan*/  num_switches; TYPE_2__* p_osm; scalar_t__ vl_min; int /*<<< orphan*/ * switches; } ;
typedef  TYPE_6__ lash_t ;
typedef  int /*<<< orphan*/  ib_port_info_t ;
struct TYPE_12__ {TYPE_4__ subn; int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  OSM_LOG_INFO ; 
 int /*<<< orphan*/ * calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_qmap_count (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_head (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_next (int /*<<< orphan*/ *) ; 
 scalar_t__ ib_port_info_get_op_vls (int /*<<< orphan*/ *) ; 
 int osm_node_get_num_physp (int /*<<< orphan*/ ) ; 
 TYPE_5__* osm_node_get_physp_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  switch_create (TYPE_6__*,int,TYPE_3__*) ; 

__attribute__((used)) static int discover_network_properties(lash_t * p_lash)
{
	int i, id = 0;
	uint8_t vl_min;
	osm_subn_t *p_subn = &p_lash->p_osm->subn;
	osm_switch_t *p_next_sw, *p_sw;
	osm_log_t *p_log = &p_lash->p_osm->log;

	p_lash->num_switches = cl_qmap_count(&p_subn->sw_guid_tbl);

	p_lash->switches = calloc(p_lash->num_switches, sizeof(switch_t *));
	if (!p_lash->switches)
		return -1;

	vl_min = 5;		/* set to a high value */

	p_next_sw = (osm_switch_t *) cl_qmap_head(&p_subn->sw_guid_tbl);
	while (p_next_sw != (osm_switch_t *) cl_qmap_end(&p_subn->sw_guid_tbl)) {
		uint16_t port_count;
		p_sw = p_next_sw;
		p_next_sw = (osm_switch_t *) cl_qmap_next(&p_sw->map_item);

		p_lash->switches[id] = switch_create(p_lash, id, p_sw);
		if (!p_lash->switches[id])
			return -1;
		id++;

		port_count = osm_node_get_num_physp(p_sw->p_node);

		/* Note, ignoring port 0. management port */
		for (i = 1; i < port_count; i++) {
			osm_physp_t *p_current_physp =
			    osm_node_get_physp_ptr(p_sw->p_node, i);

			if (p_current_physp
			    && p_current_physp->p_remote_physp) {

				ib_port_info_t *p_port_info =
				    &p_current_physp->port_info;
				uint8_t port_vl_min =
				    ib_port_info_get_op_vls(p_port_info);
				if (port_vl_min && port_vl_min < vl_min)
					vl_min = port_vl_min;
			}
		}		/* for */
	}			/* while */

	vl_min = 1 << (vl_min - 1);
	if (vl_min > 15)
		vl_min = 15;

	if (p_lash->p_osm->subn.opt.lash_start_vl >= vl_min) {
		OSM_LOG(p_log, OSM_LOG_ERROR, "ERR 4D03: "
			"Start VL(%d) too high for min operational vl(%d)\n",
			p_lash->p_osm->subn.opt.lash_start_vl, vl_min);
		return -1;
	}

	p_lash->vl_min = vl_min - p_lash->p_osm->subn.opt.lash_start_vl;

	OSM_LOG(p_log, OSM_LOG_INFO,
		"min operational vl(%d) start vl(%d) max_switches(%d)\n",
		p_lash->vl_min, p_lash->p_osm->subn.opt.lash_start_vl,
		p_lash->num_switches);
	return 0;
}