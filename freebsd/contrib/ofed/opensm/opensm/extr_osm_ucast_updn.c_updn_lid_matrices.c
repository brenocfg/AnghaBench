#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ ids_guid_file; scalar_t__ connect_roots; scalar_t__ root_guid_file; } ;
struct TYPE_13__ {int /*<<< orphan*/  sw_guid_tbl; TYPE_2__ opt; } ;
struct TYPE_11__ {int /*<<< orphan*/  ucast_mgr; } ;
struct TYPE_14__ {int num_roots; int /*<<< orphan*/  log; struct TYPE_14__* p_osm; TYPE_3__ subn; TYPE_1__ sm; } ;
typedef  TYPE_4__ updn_t ;
struct TYPE_15__ {int /*<<< orphan*/  priv; } ;
typedef  TYPE_5__ osm_switch_t ;
typedef  int /*<<< orphan*/  cl_map_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  OSM_LOG_DEBUG ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSM_LOG_INFO ; 
 scalar_t__ OSM_LOG_IS_ACTIVE_V2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_ROUTING ; 
 int /*<<< orphan*/ * cl_qmap_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_updn_node (TYPE_5__*) ; 
 int /*<<< orphan*/  delete_updn_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_roots ; 
 int /*<<< orphan*/  osm_dump_qmap_to_file (TYPE_4__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_ucast_mgr_build_lid_matrices (int /*<<< orphan*/ *) ; 
 int parse_node_map (scalar_t__,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  rank_root_node ; 
 int /*<<< orphan*/  update_id ; 
 int updn_build_lid_matrices (TYPE_4__*) ; 
 int /*<<< orphan*/  updn_find_root_nodes_by_min_hop (TYPE_4__*) ; 

__attribute__((used)) static int updn_lid_matrices(void *ctx)
{
	updn_t *p_updn = ctx;
	cl_map_item_t *item;
	osm_switch_t *p_sw;
	int ret = 0;

	OSM_LOG_ENTER(&p_updn->p_osm->log);

	for (item = cl_qmap_head(&p_updn->p_osm->subn.sw_guid_tbl);
	     item != cl_qmap_end(&p_updn->p_osm->subn.sw_guid_tbl);
	     item = cl_qmap_next(item)) {
		p_sw = (osm_switch_t *)item;
		p_sw->priv = create_updn_node(p_sw);
		if (!p_sw->priv) {
			OSM_LOG(&(p_updn->p_osm->log), OSM_LOG_ERROR, "ERR AA0C: "
				"cannot create updn node\n");
			OSM_LOG_EXIT(&p_updn->p_osm->log);
			return -1;
		}
	}

	/* First setup root nodes */
	p_updn->num_roots = 0;

	if (p_updn->p_osm->subn.opt.root_guid_file) {
		OSM_LOG(&p_updn->p_osm->log, OSM_LOG_DEBUG,
			"UPDN - Fetching root nodes from file \'%s\'\n",
			p_updn->p_osm->subn.opt.root_guid_file);

		ret = parse_node_map(p_updn->p_osm->subn.opt.root_guid_file,
				     rank_root_node, p_updn);
		if (ret) {
			OSM_LOG(&p_updn->p_osm->log, OSM_LOG_ERROR, "ERR AA02: "
				"cannot parse root guids file \'%s\'\n",
				p_updn->p_osm->subn.opt.root_guid_file);
			osm_ucast_mgr_build_lid_matrices(&p_updn->p_osm->sm.ucast_mgr);
			updn_find_root_nodes_by_min_hop(p_updn);
		} else if (p_updn->p_osm->subn.opt.connect_roots &&
			   p_updn->num_roots > 1)
			osm_ucast_mgr_build_lid_matrices(&p_updn->p_osm->sm.ucast_mgr);
	} else {
		osm_ucast_mgr_build_lid_matrices(&p_updn->p_osm->sm.ucast_mgr);
		updn_find_root_nodes_by_min_hop(p_updn);
	}

	if (p_updn->p_osm->subn.opt.ids_guid_file) {
		OSM_LOG(&p_updn->p_osm->log, OSM_LOG_DEBUG,
			"UPDN - update node ids from file \'%s\'\n",
			p_updn->p_osm->subn.opt.ids_guid_file);

		ret = parse_node_map(p_updn->p_osm->subn.opt.ids_guid_file,
				     update_id, p_updn->p_osm);
		if (ret)
			OSM_LOG(&p_updn->p_osm->log, OSM_LOG_ERROR, "ERR AA03: "
				"cannot parse node ids file \'%s\'\n",
				p_updn->p_osm->subn.opt.ids_guid_file);
	}

	/* Only if there are assigned root nodes do the algorithm, otherwise perform do nothing */
	if (p_updn->num_roots) {
		OSM_LOG(&p_updn->p_osm->log, OSM_LOG_DEBUG,
			"activating UPDN algorithm\n");
		ret = updn_build_lid_matrices(p_updn);
	} else {
		OSM_LOG(&p_updn->p_osm->log, OSM_LOG_INFO,
			"disabling UPDN algorithm, no root nodes were found\n");
		ret = -1;
	}

	if (OSM_LOG_IS_ACTIVE_V2(&p_updn->p_osm->log, OSM_LOG_ROUTING))
		osm_dump_qmap_to_file(p_updn->p_osm, "opensm-updn-roots.dump",
				      &p_updn->p_osm->subn.sw_guid_tbl,
				      dump_roots, NULL);

	for (item = cl_qmap_head(&p_updn->p_osm->subn.sw_guid_tbl);
	     item != cl_qmap_end(&p_updn->p_osm->subn.sw_guid_tbl);
	     item = cl_qmap_next(item)) {
		p_sw = (osm_switch_t *) item;
		delete_updn_node(p_sw->priv);
	}

	OSM_LOG_EXIT(&p_updn->p_osm->log);
	return ret;
}