#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct osm_routing_engine {int /*<<< orphan*/  destroy; int /*<<< orphan*/  ucast_build_fwd_tables; int /*<<< orphan*/  build_lid_matrices; void* context; } ;
struct TYPE_7__ {int /*<<< orphan*/  p_subn; } ;
struct TYPE_8__ {TYPE_1__ ucast_mgr; } ;
struct TYPE_9__ {TYPE_2__ sm; } ;
typedef  TYPE_3__ osm_opensm_t ;
struct TYPE_10__ {int /*<<< orphan*/  p_subn; TYPE_3__* p_osm; } ;
typedef  TYPE_4__ ftree_fabric_t ;

/* Variables and functions */
 int /*<<< orphan*/  construct_fabric ; 
 int /*<<< orphan*/  delete ; 
 int /*<<< orphan*/  do_routing ; 
 TYPE_4__* fabric_create () ; 

int osm_ucast_ftree_setup(struct osm_routing_engine *r, osm_opensm_t * p_osm)
{
	ftree_fabric_t *p_ftree = fabric_create();
	if (!p_ftree)
		return -1;

	p_ftree->p_osm = p_osm;
	p_ftree->p_subn = p_osm->sm.ucast_mgr.p_subn;

	r->context = (void *)p_ftree;
	r->build_lid_matrices = construct_fabric;
	r->ucast_build_fwd_tables = do_routing;
	r->destroy = delete;

	return 0;
}