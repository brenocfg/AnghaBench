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
struct TYPE_12__ {TYPE_5__* node; } ;
typedef  TYPE_4__ switch_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
struct TYPE_13__ {unsigned int num_links; TYPE_6__** links; } ;
typedef  TYPE_5__ mesh_node_t ;
struct TYPE_14__ {int switch_id; int* ports; int link_id; int /*<<< orphan*/  num_ports; } ;
typedef  TYPE_6__ link_t ;
struct TYPE_15__ {TYPE_4__** switches; TYPE_3__* p_osm; } ;
typedef  TYPE_7__ lash_t ;
struct TYPE_9__ {scalar_t__ do_mesh_analysis; } ;
struct TYPE_10__ {TYPE_1__ opt; } ;
struct TYPE_11__ {TYPE_2__ subn; int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  OSM_LOG_VERBOSE ; 

__attribute__((used)) static void connect_switches(lash_t * p_lash, int sw1, int sw2, int phy_port_1)
{
	osm_log_t *p_log = &p_lash->p_osm->log;
	unsigned num = p_lash->switches[sw1]->node->num_links;
	switch_t *s1 = p_lash->switches[sw1];
	mesh_node_t *node = s1->node;
	switch_t *s2;
	link_t *l;
	unsigned int i;

	/*
	 * if doing mesh analysis:
	 *  - do not consider connections to self
	 *  - collapse multiple connections between
	 *    pair of switches to a single locical link
	 */
	if (p_lash->p_osm->subn.opt.do_mesh_analysis) {
		if (sw1 == sw2)
			return;

		/* see if we are already linked to sw2 */
		for (i = 0; i < num; i++) {
			l = node->links[i];

			if (node->links[i]->switch_id == sw2) {
				l->ports[l->num_ports++] = phy_port_1;
				return;
			}
		}
	}

	l = node->links[num];
	l->switch_id = sw2;
	l->link_id = -1;
	l->ports[l->num_ports++] = phy_port_1;

	s2 = p_lash->switches[sw2];
	for (i = 0; i < s2->node->num_links; i++) {
		if (s2->node->links[i]->switch_id == sw1) {
			s2->node->links[i]->link_id = num;
			l->link_id = i;
			break;
		}
	}

	node->num_links++;

	OSM_LOG(p_log, OSM_LOG_VERBOSE,
		"LASH connect: %d, %d, %d\n", sw1, sw2, phy_port_1);
}