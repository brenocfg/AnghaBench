#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osm_log_t ;
struct TYPE_14__ {int type; unsigned int num_links; TYPE_2__** links; } ;
typedef  TYPE_6__ mesh_node_t ;
struct TYPE_15__ {int num_switches; TYPE_5__** switches; TYPE_1__* p_osm; } ;
typedef  TYPE_7__ lash_t ;
struct TYPE_13__ {TYPE_4__* p_sw; TYPE_6__* node; } ;
struct TYPE_12__ {TYPE_3__* p_node; } ;
struct TYPE_11__ {int /*<<< orphan*/  print_desc; } ;
struct TYPE_10__ {size_t switch_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_DEBUG ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_edges(lash_t *p_lash)
{
	osm_log_t *p_log = &p_lash->p_osm->log;
	int sw;
	mesh_node_t *n, *nn;
	unsigned i;

	OSM_LOG_ENTER(p_log);

	for (sw = 0; sw < p_lash->num_switches; sw++) {
		n = p_lash->switches[sw]->node;
		if (!n->type)
			continue;

		for (i = 0; i < n->num_links; i++) {
			nn = p_lash->switches[n->links[i]->switch_id]->node;

			if (nn->num_links > n->num_links) {
				OSM_LOG(p_log, OSM_LOG_DEBUG,
					"removed edge switch %s\n",
					p_lash->switches[sw]->p_sw->p_node->print_desc);
				n->type = -1;
				break;
			}
		}
	}

	OSM_LOG_EXIT(p_log);
}