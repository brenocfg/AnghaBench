#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ qos; scalar_t__ scatter_ports; } ;
struct TYPE_12__ {int /*<<< orphan*/  node_guid_tbl; int /*<<< orphan*/  port_guid_tbl; TYPE_1__ opt; int /*<<< orphan*/  sw_guid_tbl; } ;
struct TYPE_13__ {int /*<<< orphan*/  log; TYPE_3__ subn; TYPE_2__* routing_engine_used; } ;
typedef  TYPE_4__ osm_opensm_t ;
struct TYPE_11__ {scalar_t__ update_sl2vl; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG_DEBUG ; 
 scalar_t__ OSM_LOG_IS_ACTIVE_V2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_ROUTING ; 
 int /*<<< orphan*/  OSM_LOG_VERBOSE ; 
 int /*<<< orphan*/  dump_lid_matrix ; 
 int /*<<< orphan*/  dump_mcast_routes ; 
 int /*<<< orphan*/  dump_qmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  dump_sl2vl_tbl ; 
 int /*<<< orphan*/  dump_topology_node ; 
 int /*<<< orphan*/  dump_ucast_lfts ; 
 int /*<<< orphan*/  dump_ucast_path_distribution ; 
 int /*<<< orphan*/  dump_ucast_routes ; 
 int /*<<< orphan*/  osm_dump_qmap_to_file (TYPE_4__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  print_report (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srandom (scalar_t__) ; 
 int /*<<< orphan*/  stdout ; 

void osm_dump_all(osm_opensm_t * osm)
{
	if (OSM_LOG_IS_ACTIVE_V2(&osm->log, OSM_LOG_ROUTING)) {
		/* unicast routes */
		osm_dump_qmap_to_file(osm, "opensm-lid-matrix.dump",
				      &osm->subn.sw_guid_tbl, dump_lid_matrix,
				      osm);
		osm_dump_qmap_to_file(osm, "opensm-lfts.dump",
				      &osm->subn.sw_guid_tbl, dump_ucast_lfts,
				      osm);
		if (OSM_LOG_IS_ACTIVE_V2(&osm->log, OSM_LOG_DEBUG))
			dump_qmap(stdout, &osm->subn.sw_guid_tbl,
				  dump_ucast_path_distribution, osm);

		/* An attempt to get osm_switch_recommend_path to report the
		   same routes that a sweep would assign. */
		if (osm->subn.opt.scatter_ports)
			srandom(osm->subn.opt.scatter_ports);

		osm_dump_qmap_to_file(osm, "opensm.fdbs",
				      &osm->subn.sw_guid_tbl,
				      dump_ucast_routes, osm);
		/* multicast routes */
		osm_dump_qmap_to_file(osm, "opensm.mcfdbs",
				      &osm->subn.sw_guid_tbl,
				      dump_mcast_routes, osm);
		/* SL2VL tables */
		if (osm->subn.opt.qos ||
		    (osm->routing_engine_used &&
		     osm->routing_engine_used->update_sl2vl))
			osm_dump_qmap_to_file(osm, "opensm-sl2vl.dump",
					      &osm->subn.port_guid_tbl,
					      dump_sl2vl_tbl, osm);
	}
	osm_dump_qmap_to_file(osm, "opensm-subnet.lst",
			      &osm->subn.node_guid_tbl, dump_topology_node,
			      osm);
	if (OSM_LOG_IS_ACTIVE_V2(&osm->log, OSM_LOG_VERBOSE))
		print_report(osm, stdout);
}