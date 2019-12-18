#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct osm_routing_engine {int /*<<< orphan*/  build_lid_matrices; int /*<<< orphan*/  destroy; TYPE_2__* context; } ;
struct TYPE_6__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ osm_opensm_t ;
struct TYPE_7__ {TYPE_1__* p_osm; } ;
typedef  TYPE_2__ dnup_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dnup_delete ; 
 int /*<<< orphan*/  dnup_lid_matrices ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int osm_ucast_dnup_setup(struct osm_routing_engine *r, osm_opensm_t *osm)
{
	dnup_t *dnup;

	OSM_LOG_ENTER(&osm->log);

	dnup = malloc(sizeof(dnup_t));
	if (!dnup)
		return -1;
	memset(dnup, 0, sizeof(dnup_t));

	dnup->p_osm = osm;

	r->context = dnup;
	r->destroy = dnup_delete;
	r->build_lid_matrices = dnup_lid_matrices;

	OSM_LOG_EXIT(&osm->log);
	return 0;
}