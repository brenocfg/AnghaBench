#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_13__ {int sm_priority; int sweep_interval; } ;
struct TYPE_14__ {int sweeping_enabled; int ignore_existing_lfts; int subnet_initialization_error; int in_sweep_hop_0; int first_time_master_sweep; int coming_out_of_standby; TYPE_4__ opt; int /*<<< orphan*/  sm_state; } ;
struct TYPE_12__ {scalar_t__ sa_mads_ignored; scalar_t__ sa_mads_rcvd_unknown; scalar_t__ sa_mads_sent; scalar_t__ sa_mads_rcvd; scalar_t__ sa_mads_outstanding; scalar_t__ qp0_mads_rcvd_unknown; scalar_t__ qp0_unicasts_sent; scalar_t__ qp0_mads_sent; scalar_t__ qp0_mads_rcvd; scalar_t__ qp0_mads_outstanding_on_wire; scalar_t__ qp0_mads_outstanding; } ;
struct TYPE_10__ {int /*<<< orphan*/  state; } ;
struct TYPE_15__ {char* osm_version; int /*<<< orphan*/  lock; TYPE_5__ subn; TYPE_3__ stats; int /*<<< orphan*/  perfmgr; int /*<<< orphan*/  plugin_list; TYPE_2__* routing_engine_used; TYPE_1__ sa; } ;
typedef  TYPE_6__ osm_opensm_t ;
struct TYPE_16__ {char* plugin_name; } ;
typedef  TYPE_7__ osm_epi_plugin_t ;
typedef  int /*<<< orphan*/  cl_list_item_t ;
struct TYPE_11__ {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_ROUTING_ENGINE_TYPE_NONE ; 
 int /*<<< orphan*/  cl_plock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_plock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qlist_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qlist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qlist_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_sms (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* osm_perfmgr_get_state_str (int /*<<< orphan*/ *) ; 
 char* osm_perfmgr_get_sweep_state_str (int /*<<< orphan*/ *) ; 
 char* osm_routing_engine_type_str (int /*<<< orphan*/ ) ; 
 char* sa_state_str (int /*<<< orphan*/ ) ; 
 char* sm_state_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_status(osm_opensm_t * p_osm, FILE * out)
{
	cl_list_item_t *item;

	if (out) {
		const char *re_str;

		cl_plock_acquire(&p_osm->lock);
		fprintf(out, "   OpenSM Version       : %s\n", p_osm->osm_version);
		fprintf(out, "   SM State             : %s\n",
			sm_state_str(p_osm->subn.sm_state));
		fprintf(out, "   SM Priority          : %d\n",
			p_osm->subn.opt.sm_priority);
		fprintf(out, "   SA State             : %s\n",
			sa_state_str(p_osm->sa.state));

		re_str = p_osm->routing_engine_used ?
			osm_routing_engine_type_str(p_osm->routing_engine_used->type) :
			osm_routing_engine_type_str(OSM_ROUTING_ENGINE_TYPE_NONE);
		fprintf(out, "   Routing Engine       : %s\n", re_str);

		fprintf(out, "   Loaded event plugins :");
		if (cl_qlist_head(&p_osm->plugin_list) ==
			cl_qlist_end(&p_osm->plugin_list)) {
			fprintf(out, " <none>");
		}
		for (item = cl_qlist_head(&p_osm->plugin_list);
		     item != cl_qlist_end(&p_osm->plugin_list);
		     item = cl_qlist_next(item))
			fprintf(out, " %s",
				((osm_epi_plugin_t *)item)->plugin_name);
		fprintf(out, "\n");

#ifdef ENABLE_OSM_PERF_MGR
		fprintf(out, "\n   PerfMgr state/sweep state : %s/%s\n",
			osm_perfmgr_get_state_str(&p_osm->perfmgr),
			osm_perfmgr_get_sweep_state_str(&p_osm->perfmgr));
#endif
		fprintf(out, "\n   MAD stats\n"
			"   ---------\n"
			"   QP0 MADs outstanding           : %u\n"
			"   QP0 MADs outstanding (on wire) : %u\n"
			"   QP0 MADs rcvd                  : %u\n"
			"   QP0 MADs sent                  : %u\n"
			"   QP0 unicasts sent              : %u\n"
			"   QP0 unknown MADs rcvd          : %u\n"
			"   SA MADs outstanding            : %u\n"
			"   SA MADs rcvd                   : %u\n"
			"   SA MADs sent                   : %u\n"
			"   SA unknown MADs rcvd           : %u\n"
			"   SA MADs ignored                : %u\n",
			(uint32_t)p_osm->stats.qp0_mads_outstanding,
			(uint32_t)p_osm->stats.qp0_mads_outstanding_on_wire,
			(uint32_t)p_osm->stats.qp0_mads_rcvd,
			(uint32_t)p_osm->stats.qp0_mads_sent,
			(uint32_t)p_osm->stats.qp0_unicasts_sent,
			(uint32_t)p_osm->stats.qp0_mads_rcvd_unknown,
			(uint32_t)p_osm->stats.sa_mads_outstanding,
			(uint32_t)p_osm->stats.sa_mads_rcvd,
			(uint32_t)p_osm->stats.sa_mads_sent,
			(uint32_t)p_osm->stats.sa_mads_rcvd_unknown,
			(uint32_t)p_osm->stats.sa_mads_ignored);
		fprintf(out, "\n   Subnet flags\n"
			"   ------------\n"
			"   Sweeping enabled               : %d\n"
			"   Sweep interval (seconds)       : %u\n"
			"   Ignore existing lfts           : %d\n"
			"   Subnet Init errors             : %d\n"
			"   In sweep hop 0                 : %d\n"
			"   First time master sweep        : %d\n"
			"   Coming out of standby          : %d\n",
			p_osm->subn.sweeping_enabled,
			p_osm->subn.opt.sweep_interval,
			p_osm->subn.ignore_existing_lfts,
			p_osm->subn.subnet_initialization_error,
			p_osm->subn.in_sweep_hop_0,
			p_osm->subn.first_time_master_sweep,
			p_osm->subn.coming_out_of_standby);
		dump_sms(p_osm, out);
		fprintf(out, "\n");
		cl_plock_release(&p_osm->lock);
	}
}