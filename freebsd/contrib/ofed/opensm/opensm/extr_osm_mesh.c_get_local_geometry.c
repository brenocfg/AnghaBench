#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osm_log_t ;
typedef  int /*<<< orphan*/  mesh_t ;
struct TYPE_13__ {int num_switches; TYPE_3__** switches; TYPE_1__* p_osm; } ;
typedef  TYPE_4__ lash_t ;
struct TYPE_12__ {TYPE_2__* node; } ;
struct TYPE_11__ {scalar_t__ num_links; scalar_t__ type; } ;
struct TYPE_10__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ MAX_DEGREE ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  classify_mesh_type (TYPE_4__*,int) ; 
 int /*<<< orphan*/  classify_switch (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_switch_metric (TYPE_4__*,int) ; 
 int /*<<< orphan*/  remove_edges (TYPE_4__*) ; 

__attribute__((used)) static int get_local_geometry(lash_t *p_lash, mesh_t *mesh)
{
	osm_log_t *p_log = &p_lash->p_osm->log;
	int sw;
	int status = 0;

	OSM_LOG_ENTER(p_log);

	for (sw = 0; sw < p_lash->num_switches; sw++) {
		/*
		 * skip switches with more links than MAX_DEGREE
		 * since they will never match a known case
		 */
		if (p_lash->switches[sw]->node->num_links > MAX_DEGREE)
			continue;

		if (get_switch_metric(p_lash, sw)) {
			status = -1;
			goto Exit;
		}
		classify_mesh_type(p_lash, sw);
	}

	remove_edges(p_lash);

	for (sw = 0; sw < p_lash->num_switches; sw++) {
		if (p_lash->switches[sw]->node->type < 0)
			continue;
		classify_switch(p_lash, mesh, sw);
	}

Exit:
	OSM_LOG_EXIT(p_log);
	return status;
}