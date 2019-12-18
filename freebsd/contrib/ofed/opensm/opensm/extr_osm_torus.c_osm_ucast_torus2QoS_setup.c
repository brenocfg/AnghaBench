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
struct torus_context {int dummy; } ;
struct osm_routing_engine {int /*<<< orphan*/  destroy; int /*<<< orphan*/  mcast_build_stree; int /*<<< orphan*/  path_sl; int /*<<< orphan*/  update_vlarb; int /*<<< orphan*/  update_sl2vl; int /*<<< orphan*/  build_lid_matrices; int /*<<< orphan*/  ucast_build_fwd_tables; struct torus_context* context; } ;
typedef  int /*<<< orphan*/  osm_opensm_t ;

/* Variables and functions */
 int /*<<< orphan*/  torus_build_lfts ; 
 struct torus_context* torus_context_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torus_context_delete ; 
 int /*<<< orphan*/  torus_mcast_stree ; 
 int /*<<< orphan*/  torus_path_sl ; 
 int /*<<< orphan*/  torus_update_osm_sl2vl ; 
 int /*<<< orphan*/  torus_update_osm_vlarb ; 
 int /*<<< orphan*/  ucast_dummy_build_lid_matrices ; 

int osm_ucast_torus2QoS_setup(struct osm_routing_engine *r,
			      osm_opensm_t *osm)
{
	struct torus_context *ctx;

	ctx = torus_context_create(osm);
	if (!ctx)
		return -1;

	r->context = ctx;
	r->ucast_build_fwd_tables = torus_build_lfts;
	r->build_lid_matrices = ucast_dummy_build_lid_matrices;
	r->update_sl2vl = torus_update_osm_sl2vl;
	r->update_vlarb = torus_update_osm_vlarb;
	r->path_sl = torus_path_sl;
	r->mcast_build_stree = torus_mcast_stree;
	r->destroy = torus_context_delete;
	return 0;
}