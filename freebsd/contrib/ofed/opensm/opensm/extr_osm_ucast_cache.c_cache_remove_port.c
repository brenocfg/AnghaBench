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
typedef  size_t uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_log; int /*<<< orphan*/  cache_valid; } ;
typedef  TYPE_2__ osm_ucast_mgr_t ;
struct TYPE_10__ {size_t num_ports; TYPE_1__* ports; } ;
typedef  TYPE_3__ cache_switch_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_8__ {scalar_t__ is_leaf; scalar_t__ remote_lid_ho; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,size_t,...) ; 
 int /*<<< orphan*/  OSM_LOG_DEBUG ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ ) ; 
 TYPE_3__* cache_get_sw (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  osm_ucast_cache_invalidate (TYPE_2__*) ; 

__attribute__((used)) static void cache_remove_port(osm_ucast_mgr_t * p_mgr, uint16_t lid_ho,
			      uint8_t port_num, uint16_t remote_lid_ho,
			      boolean_t is_ca)
{
	cache_switch_t *p_cache_sw;

	OSM_LOG_ENTER(p_mgr->p_log);

	if (!p_mgr->cache_valid)
		goto Exit;

	p_cache_sw = cache_get_sw(p_mgr, lid_ho);
	if (!p_cache_sw) {
		OSM_LOG(p_mgr->p_log, OSM_LOG_DEBUG,
			"Found uncached switch/link (lid %u, port %u)\n",
			lid_ho, port_num);
		osm_ucast_cache_invalidate(p_mgr);
		goto Exit;
	}

	if (port_num >= p_cache_sw->num_ports ||
	    !p_cache_sw->ports[port_num].remote_lid_ho) {
		OSM_LOG(p_mgr->p_log, OSM_LOG_DEBUG,
			"Found uncached switch link (lid %u, port %u)\n",
			lid_ho, port_num);
		osm_ucast_cache_invalidate(p_mgr);
		goto Exit;
	}

	if (p_cache_sw->ports[port_num].remote_lid_ho != remote_lid_ho) {
		OSM_LOG(p_mgr->p_log, OSM_LOG_DEBUG,
			"Remote lid change on switch lid %u, port %u "
			"(was %u, now %u)\n", lid_ho, port_num,
			p_cache_sw->ports[port_num].remote_lid_ho,
			remote_lid_ho);
		osm_ucast_cache_invalidate(p_mgr);
		goto Exit;
	}

	if ((p_cache_sw->ports[port_num].is_leaf && !is_ca) ||
	    (!p_cache_sw->ports[port_num].is_leaf && is_ca)) {
		OSM_LOG(p_mgr->p_log, OSM_LOG_DEBUG,
			"Remote node type change on switch lid %u, port %u\n",
			lid_ho, port_num);
		osm_ucast_cache_invalidate(p_mgr);
		goto Exit;
	}

	OSM_LOG(p_mgr->p_log, OSM_LOG_DEBUG,
		"New link from lid %u, port %u to lid %u - "
		"found in cache\n", lid_ho, port_num, remote_lid_ho);

	/* the new link was cached - clean it from the cache */

	p_cache_sw->ports[port_num].remote_lid_ho = 0;
	p_cache_sw->ports[port_num].is_leaf = FALSE;
Exit:
	OSM_LOG_EXIT(p_mgr->p_log);
}