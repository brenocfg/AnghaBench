#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct qos_config {int /*<<< orphan*/  vl_high_limit; int /*<<< orphan*/  sl2vl; } ;
struct osm_routing_engine {int /*<<< orphan*/  context; int /*<<< orphan*/  (* update_sl2vl ) (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_16__ {TYPE_2__* p_subn; } ;
typedef  TYPE_4__ osm_sm_t ;
struct TYPE_15__ {int capability_mask; } ;
struct TYPE_17__ {TYPE_3__ port_info; int /*<<< orphan*/  vl_high_limit; scalar_t__ need_update; } ;
typedef  TYPE_5__ osm_physp_t ;
typedef  int /*<<< orphan*/  ib_slvl_table_t ;
typedef  int /*<<< orphan*/  cl_qlist_t ;
struct TYPE_14__ {TYPE_1__* p_osm; scalar_t__ need_update; } ;
struct TYPE_13__ {struct osm_routing_engine* routing_engine_used; } ;

/* Variables and functions */
 int IB_PORT_CAP_HAS_SL_MAP ; 
 scalar_t__ sl2vl_update_table (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vlarb_update (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ,unsigned int,struct qos_config const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qos_endport_setup(osm_sm_t * sm, osm_physp_t * p,
			     const struct qos_config *qcfg, int vlarb_only,
			     cl_qlist_t *port_mad_list)
{
	unsigned force_update = p->need_update || sm->p_subn->need_update;
	struct osm_routing_engine *re = sm->p_subn->p_osm->routing_engine_used;
	const ib_slvl_table_t *port_sl2vl = &qcfg->sl2vl;
	ib_slvl_table_t routing_sl2vl;

	p->vl_high_limit = qcfg->vl_high_limit;
	if (vlarb_update(sm, p, 0, force_update, qcfg, port_mad_list))
		return -1;
	if (vlarb_only)
		return 0;

	if (!(p->port_info.capability_mask & IB_PORT_CAP_HAS_SL_MAP))
		return 0;

	if (re && re->update_sl2vl) {
		routing_sl2vl = *port_sl2vl;
		re->update_sl2vl(re->context, p, 0, 0, &routing_sl2vl);
		port_sl2vl = &routing_sl2vl;
	}
	if (sl2vl_update_table(sm, p, 0, 0, force_update, port_sl2vl,
			       port_mad_list))
		return -1;

	return 0;
}