#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {TYPE_3__* routing_table; } ;
typedef  TYPE_4__ switch_t ;
struct TYPE_15__ {scalar_t__ priv; } ;
typedef  TYPE_5__ osm_switch_t ;
typedef  int /*<<< orphan*/  osm_port_t ;
struct TYPE_12__ {int /*<<< orphan*/  lash_start_vl; } ;
struct TYPE_18__ {TYPE_2__ opt; } ;
struct TYPE_16__ {TYPE_8__ subn; TYPE_1__* routing_engine_used; } ;
typedef  TYPE_6__ osm_opensm_t ;
struct TYPE_17__ {TYPE_6__* p_osm; } ;
typedef  TYPE_7__ lash_t ;
typedef  int /*<<< orphan*/  ib_net16_t ;
struct TYPE_13__ {int /*<<< orphan*/  lane; } ;
struct TYPE_11__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_DEFAULT_SL ; 
 scalar_t__ OSM_ROUTING_ENGINE_TYPE_LASH ; 
 unsigned int get_lash_id (TYPE_5__*) ; 
 TYPE_5__* get_osm_switch_from_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * osm_get_port_by_lid (TYPE_8__*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static uint8_t get_lash_sl(void *context, uint8_t path_sl_hint,
			   const ib_net16_t slid, const ib_net16_t dlid)
{
	unsigned dst_id;
	unsigned src_id;
	osm_port_t *p_src_port, *p_dst_port;
	osm_switch_t *p_sw;
	lash_t *p_lash = context;
	osm_opensm_t *p_osm = p_lash->p_osm;

	if (!(p_osm->routing_engine_used &&
	      p_osm->routing_engine_used->type == OSM_ROUTING_ENGINE_TYPE_LASH))
		return OSM_DEFAULT_SL;

	p_src_port = osm_get_port_by_lid(&p_osm->subn, slid);
	if (!p_src_port)
		return OSM_DEFAULT_SL;

	p_dst_port = osm_get_port_by_lid(&p_osm->subn, dlid);
	if (!p_dst_port)
		return OSM_DEFAULT_SL;

	p_sw = get_osm_switch_from_port(p_dst_port);
	if (!p_sw || !p_sw->priv)
		return OSM_DEFAULT_SL;
	dst_id = get_lash_id(p_sw);

	p_sw = get_osm_switch_from_port(p_src_port);
	if (!p_sw || !p_sw->priv)
		return OSM_DEFAULT_SL;

	src_id = get_lash_id(p_sw);
	if (src_id == dst_id)
		return p_osm->subn.opt.lash_start_vl;

	return (uint8_t) ((switch_t *) p_sw->priv)->routing_table[dst_id].lane;
}