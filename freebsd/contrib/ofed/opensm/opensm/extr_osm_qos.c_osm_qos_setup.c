#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct qos_config {int /*<<< orphan*/  sl2vl; } ;
struct TYPE_26__ {int /*<<< orphan*/  list_item; int /*<<< orphan*/  port_mad_list; } ;
typedef  TYPE_5__ qos_mad_list_t ;
struct TYPE_27__ {int /*<<< orphan*/  p_madw; } ;
typedef  TYPE_6__ qos_mad_item_t ;
struct TYPE_28__ {int /*<<< orphan*/  p_physp; TYPE_9__* p_node; } ;
typedef  TYPE_7__ osm_port_t ;
struct TYPE_20__ {TYPE_4__* p_subn; } ;
struct TYPE_22__ {int /*<<< orphan*/  qos_options; int /*<<< orphan*/  qos_rtr_options; int /*<<< orphan*/  qos_swe_options; int /*<<< orphan*/  qos_sw0_options; int /*<<< orphan*/  qos_ca_options; int /*<<< orphan*/  qos; } ;
struct TYPE_21__ {int /*<<< orphan*/  port_guid_tbl; TYPE_1__ opt; } ;
struct TYPE_29__ {int /*<<< orphan*/  log; int /*<<< orphan*/  lock; TYPE_10__ sm; TYPE_15__ subn; } ;
typedef  TYPE_8__ osm_opensm_t ;
struct TYPE_30__ {TYPE_2__* sw; } ;
typedef  TYPE_9__ osm_node_t ;
typedef  int /*<<< orphan*/  cl_qmap_t ;
typedef  int /*<<< orphan*/  cl_qlist_t ;
typedef  int /*<<< orphan*/  cl_map_item_t ;
struct TYPE_24__ {scalar_t__ use_optimized_slvl; } ;
struct TYPE_25__ {TYPE_3__ opt; } ;
struct TYPE_23__ {int /*<<< orphan*/  switch_info; } ;

/* Variables and functions */
 scalar_t__ IB_NODE_TYPE_ROUTER ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_plock_excl_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_plock_release (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qlist_count (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qlist_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qlist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qlist_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qlist_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qlist_next (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qlist_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qlist_remove_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 scalar_t__ ib_switch_info_get_opt_sl2vlmapping (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_switch_info_is_enhanced_port0 (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osm_node_get_type (TYPE_9__*) ; 
 int /*<<< orphan*/  osm_qos_mad_delete (TYPE_6__**) ; 
 int /*<<< orphan*/  osm_qos_parse_policy_file (TYPE_15__*) ; 
 int /*<<< orphan*/  osm_send_req_mad (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qos_build_config (struct qos_config*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ qos_endport_setup (TYPE_10__*,int /*<<< orphan*/ ,struct qos_config*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ qos_extports_setup (TYPE_10__*,TYPE_9__*,struct qos_config*,int /*<<< orphan*/ *) ; 

int osm_qos_setup(osm_opensm_t * p_osm)
{
	struct qos_config ca_config, sw0_config, swe_config, rtr_config;
	struct qos_config *cfg;
	cl_qmap_t *p_tbl;
	cl_map_item_t *p_next;
	osm_port_t *p_port;
	osm_node_t *p_node;
	int ret = 0;
	int vlarb_only;
	qos_mad_list_t *p_list, *p_list_next;
	qos_mad_item_t *p_port_mad;
	cl_qlist_t qos_mad_list;

	if (!p_osm->subn.opt.qos)
		return 0;

	OSM_LOG_ENTER(&p_osm->log);

	qos_build_config(&ca_config, &p_osm->subn.opt.qos_ca_options,
			 &p_osm->subn.opt.qos_options);
	qos_build_config(&sw0_config, &p_osm->subn.opt.qos_sw0_options,
			 &p_osm->subn.opt.qos_options);
	qos_build_config(&swe_config, &p_osm->subn.opt.qos_swe_options,
			 &p_osm->subn.opt.qos_options);
	qos_build_config(&rtr_config, &p_osm->subn.opt.qos_rtr_options,
			 &p_osm->subn.opt.qos_options);

	cl_qlist_init(&qos_mad_list);

	cl_plock_excl_acquire(&p_osm->lock);

	/* read QoS policy config file */
	osm_qos_parse_policy_file(&p_osm->subn);
	p_tbl = &p_osm->subn.port_guid_tbl;
	p_next = cl_qmap_head(p_tbl);
	while (p_next != cl_qmap_end(p_tbl)) {
		vlarb_only = 0;
		p_port = (osm_port_t *) p_next;
		p_next = cl_qmap_next(p_next);

		p_list = (qos_mad_list_t *) malloc(sizeof(*p_list));
		if (!p_list) {
			cl_plock_release(&p_osm->lock);
			return -1;
		}

		memset(p_list, 0, sizeof(*p_list));

		cl_qlist_init(&p_list->port_mad_list);

		p_node = p_port->p_node;
		if (p_node->sw) {
			if (qos_extports_setup(&p_osm->sm, p_node, &swe_config,
					       &p_list->port_mad_list)) {
				cl_plock_release(&p_osm->lock);
				ret = -1;
			}

			/* skip base port 0 */
			if (!ib_switch_info_is_enhanced_port0
			    (&p_node->sw->switch_info))
				goto Continue;

			if (ib_switch_info_get_opt_sl2vlmapping(&p_node->sw->switch_info) &&
			    p_osm->sm.p_subn->opt.use_optimized_slvl &&
			    !memcmp(&swe_config.sl2vl, &sw0_config.sl2vl,
				    sizeof(swe_config.sl2vl)))
				vlarb_only = 1;

			cfg = &sw0_config;
		} else if (osm_node_get_type(p_node) == IB_NODE_TYPE_ROUTER)
			cfg = &rtr_config;
		else
			cfg = &ca_config;

		if (qos_endport_setup(&p_osm->sm, p_port->p_physp, cfg,
				      vlarb_only, &p_list->port_mad_list)) {
			cl_plock_release(&p_osm->lock);
			ret = -1;
		}
Continue:
		/* if MAD list is not empty, add it to the global MAD list */
		if (cl_qlist_count(&p_list->port_mad_list)) {
			cl_qlist_insert_tail(&qos_mad_list, &p_list->list_item);
		} else {
			free(p_list);
		}
	}
	while (cl_qlist_count(&qos_mad_list)) {
		p_list_next = (qos_mad_list_t *) cl_qlist_head(&qos_mad_list);
		while (p_list_next !=
			(qos_mad_list_t *) cl_qlist_end(&qos_mad_list)) {
			p_list = p_list_next;
			p_list_next = (qos_mad_list_t *)
				      cl_qlist_next(&p_list->list_item);
			/* next MAD to send*/
			p_port_mad = (qos_mad_item_t *)
				     cl_qlist_remove_head(&p_list->port_mad_list);
			osm_send_req_mad(&p_osm->sm, p_port_mad->p_madw);
			osm_qos_mad_delete(&p_port_mad);
			/* remove the QoS MAD from global MAD list */
			if (cl_qlist_count(&p_list->port_mad_list) == 0) {
				cl_qlist_remove_item(&qos_mad_list, &p_list->list_item);
				free(p_list);
			}
		}
	}

	cl_plock_release(&p_osm->lock);
	OSM_LOG_EXIT(&p_osm->log);

	return ret;
}