#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct osm_routing_engine {int /*<<< orphan*/  destroy; int /*<<< orphan*/  mcast_build_stree; int /*<<< orphan*/  ucast_build_fwd_tables; int /*<<< orphan*/  build_lid_matrices; void* context; } ;
typedef  int /*<<< orphan*/  osm_opensm_t ;
typedef  int /*<<< orphan*/  dfsssp_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_ROUTING_ENGINE_TYPE_SSSP ; 
 int /*<<< orphan*/  delete ; 
 int /*<<< orphan*/  dfsssp_build_graph ; 
 int /*<<< orphan*/ * dfsssp_context_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfsssp_do_dijkstra_routing ; 
 int /*<<< orphan*/  dfsssp_do_mcast_routing ; 

int osm_ucast_sssp_setup(struct osm_routing_engine *r, osm_opensm_t * p_osm)
{
	/* create context container and add ucast management object */
	dfsssp_context_t *dfsssp_context =
	    dfsssp_context_create(p_osm, OSM_ROUTING_ENGINE_TYPE_SSSP);
	if (!dfsssp_context) {
		return 1;	/* alloc failed -> skip this routing */
	}

	/* reset function pointers to sssp routines */
	r->context = (void *)dfsssp_context;
	r->build_lid_matrices = dfsssp_build_graph;
	r->ucast_build_fwd_tables = dfsssp_do_dijkstra_routing;
	r->mcast_build_stree = dfsssp_do_mcast_routing;
	r->destroy = delete;

	return 0;
}