#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osm_log_t ;
typedef  int /*<<< orphan*/  mesh_t ;
struct TYPE_6__ {int num_switches; TYPE_1__* p_osm; } ;
typedef  TYPE_2__ lash_t ;
struct TYPE_5__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ *) ; 
 scalar_t__ reorder_node_links (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int reorder_links(lash_t *p_lash, mesh_t *mesh)
{
	osm_log_t *p_log = &p_lash->p_osm->log;
	int sw;
	int num_switches = p_lash->num_switches;

	OSM_LOG_ENTER(p_log);

	for (sw = 0; sw < num_switches; sw++) {
		if (reorder_node_links(p_lash, mesh, sw)) {
			OSM_LOG_EXIT(p_log);
			return -1;
		}
	}

	OSM_LOG_EXIT(p_log);
	return 0;
}