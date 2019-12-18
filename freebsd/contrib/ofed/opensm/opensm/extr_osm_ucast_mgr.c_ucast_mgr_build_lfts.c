#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  port_order_list; TYPE_2__* p_subn; int /*<<< orphan*/  p_log; } ;
typedef  TYPE_3__ osm_ucast_mgr_t ;
struct TYPE_8__ {scalar_t__ port_prof_ignore_file; scalar_t__ guid_routing_order_file; } ;
struct TYPE_9__ {int /*<<< orphan*/  sw_guid_tbl; int /*<<< orphan*/  port_guid_tbl; TYPE_1__ opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  OSM_LOG_DEBUG ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  add_guid_to_order_list ; 
 int /*<<< orphan*/  add_port_to_order_list ; 
 int /*<<< orphan*/  cl_qlist_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qlist_remove_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qmap_apply_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  clear_prof_ignore_flag ; 
 int /*<<< orphan*/  mark_ignored_port ; 
 scalar_t__ parse_node_map (scalar_t__,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  sort_ports_by_switch_load (TYPE_3__*) ; 
 int /*<<< orphan*/  ucast_mgr_process_tbl ; 

__attribute__((used)) static int ucast_mgr_build_lfts(osm_ucast_mgr_t * p_mgr)
{
	cl_qlist_init(&p_mgr->port_order_list);

	if (p_mgr->p_subn->opt.guid_routing_order_file) {
		OSM_LOG(p_mgr->p_log, OSM_LOG_DEBUG,
			"Fetching guid routing order file \'%s\'\n",
			p_mgr->p_subn->opt.guid_routing_order_file);

		if (parse_node_map(p_mgr->p_subn->opt.guid_routing_order_file,
				   add_guid_to_order_list, p_mgr))
			OSM_LOG(p_mgr->p_log, OSM_LOG_ERROR, "ERR 3A0D: "
				"cannot parse guid routing order file \'%s\'\n",
				p_mgr->p_subn->opt.guid_routing_order_file);
	}
	sort_ports_by_switch_load(p_mgr);

	if (p_mgr->p_subn->opt.port_prof_ignore_file) {
		cl_qmap_apply_func(&p_mgr->p_subn->sw_guid_tbl,
				   clear_prof_ignore_flag, NULL);
		if (parse_node_map(p_mgr->p_subn->opt.port_prof_ignore_file,
				   mark_ignored_port, p_mgr)) {
			OSM_LOG(p_mgr->p_log, OSM_LOG_ERROR, "ERR 3A0E: "
				"cannot parse port prof ignore file \'%s\'\n",
				p_mgr->p_subn->opt.port_prof_ignore_file);
		}
	}

	cl_qmap_apply_func(&p_mgr->p_subn->port_guid_tbl,
			   add_port_to_order_list, p_mgr);

	cl_qmap_apply_func(&p_mgr->p_subn->sw_guid_tbl, ucast_mgr_process_tbl,
			   p_mgr);

	cl_qlist_remove_all(&p_mgr->port_order_list);

	return 0;
}