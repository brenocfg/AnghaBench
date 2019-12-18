#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct osm_routing_engine {int /*<<< orphan*/  ucast_build_fwd_tables; int /*<<< orphan*/  build_lid_matrices; int /*<<< orphan*/ * context; } ;
struct TYPE_4__ {int /*<<< orphan*/  ucast_mgr; } ;
struct TYPE_5__ {TYPE_1__ sm; } ;
typedef  TYPE_2__ osm_opensm_t ;

/* Variables and functions */
 int /*<<< orphan*/  ucast_build_lid_matrices ; 
 int /*<<< orphan*/  ucast_dor_build_lfts ; 

int osm_ucast_dor_setup(struct osm_routing_engine *r, osm_opensm_t * osm)
{
	r->context = &osm->sm.ucast_mgr;
	r->build_lid_matrices = ucast_build_lid_matrices;
	r->ucast_build_fwd_tables = ucast_dor_build_lfts;
	return 0;
}