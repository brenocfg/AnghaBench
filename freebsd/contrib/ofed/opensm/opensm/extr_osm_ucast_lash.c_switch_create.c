#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {unsigned int id; struct TYPE_13__* dij_channels; TYPE_3__* p_sw; TYPE_1__* routing_table; } ;
typedef  TYPE_2__ switch_t ;
struct TYPE_14__ {unsigned int num_ports; TYPE_2__* priv; } ;
typedef  TYPE_3__ osm_switch_t ;
struct TYPE_15__ {unsigned int num_switches; } ;
typedef  TYPE_4__ lash_t ;
struct TYPE_12__ {void* lane; void* out_link; } ;

/* Variables and functions */
 void* NONE ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 void* malloc (unsigned int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osm_mesh_node_create (TYPE_4__*,TYPE_2__*) ; 

__attribute__((used)) static switch_t *switch_create(lash_t * p_lash, unsigned id, osm_switch_t * p_sw)
{
	unsigned num_switches = p_lash->num_switches;
	unsigned num_ports = p_sw->num_ports;
	switch_t *sw;
	unsigned int i;

	sw = malloc(sizeof(*sw) + num_switches * sizeof(sw->routing_table[0]));
	if (!sw)
		return NULL;

	memset(sw, 0, sizeof(*sw));
	for (i = 0; i < num_switches; i++) {
		sw->routing_table[i].out_link = NONE;
		sw->routing_table[i].lane = NONE;
	}

	sw->id = id;
	sw->dij_channels = malloc(num_ports * sizeof(int));
	if (!sw->dij_channels) {
		free(sw);
		return NULL;
	}

	sw->p_sw = p_sw;
	p_sw->priv = sw;

	if (osm_mesh_node_create(p_lash, sw)) {
		free(sw->dij_channels);
		free(sw);
		return NULL;
	}

	return sw;
}