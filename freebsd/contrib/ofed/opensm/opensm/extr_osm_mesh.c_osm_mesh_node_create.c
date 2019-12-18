#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_5__* node; TYPE_2__* p_sw; } ;
typedef  TYPE_4__ switch_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
struct TYPE_15__ {TYPE_3__** links; void* axes; } ;
typedef  TYPE_5__ mesh_node_t ;
typedef  int /*<<< orphan*/  link_t ;
struct TYPE_16__ {TYPE_1__* p_osm; } ;
typedef  TYPE_6__ lash_t ;
struct TYPE_13__ {int /*<<< orphan*/  switch_id; } ;
struct TYPE_12__ {unsigned int num_ports; } ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NONE ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ *) ; 
 void* calloc (unsigned int,int) ; 
 int /*<<< orphan*/  osm_mesh_node_delete (TYPE_6__*,TYPE_4__*) ; 

int osm_mesh_node_create(lash_t *p_lash, switch_t *sw)
{
	osm_log_t *p_log = &p_lash->p_osm->log;
	unsigned i;
	mesh_node_t *node;
	unsigned num_ports = sw->p_sw->num_ports;

	OSM_LOG_ENTER(p_log);

	if (!(node = sw->node = calloc(1, sizeof(mesh_node_t) + num_ports * sizeof(link_t *))))
		goto err;

	for (i = 0; i < num_ports; i++)
		if (!(node->links[i] = calloc(1, sizeof(link_t) + num_ports * sizeof(int))))
			goto err;

	if (!(node->axes = calloc(num_ports, sizeof(int))))
		goto err;

	for (i = 0; i < num_ports; i++) {
		node->links[i]->switch_id = NONE;
	}

	OSM_LOG_EXIT(p_log);
	return 0;

err:
	osm_mesh_node_delete(p_lash, sw);
	OSM_LOG(p_log, OSM_LOG_ERROR,
		"Failed allocating mesh node - out of memory\n");
	OSM_LOG_EXIT(p_log);
	return -1;
}