#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int used_channels; int* dij_channels; size_t id; TYPE_1__* routing_table; } ;
typedef  TYPE_2__ switch_t ;
struct TYPE_10__ {size_t switch_id; struct TYPE_10__* next; } ;
typedef  TYPE_3__ reachable_dest_t ;
struct TYPE_11__ {TYPE_2__** switches; } ;
typedef  TYPE_4__ lash_t ;
struct TYPE_8__ {scalar_t__ out_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ NONE ; 
 scalar_t__ get_phys_connection (TYPE_2__*,int) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static int generate_routing_func_for_mst(lash_t * p_lash, int sw_id,
					 reachable_dest_t ** destinations)
{
	int i, next_switch;
	switch_t *sw = p_lash->switches[sw_id];
	int num_channels = sw->used_channels;
	reachable_dest_t *dest, *i_dest, *concat_dest = NULL, *prev;

	for (i = 0; i < num_channels; i++) {
		next_switch = sw->dij_channels[i];
		if (generate_routing_func_for_mst(p_lash, next_switch, &dest))
			return -1;

		i_dest = dest;
		prev = i_dest;

		while (i_dest != NULL) {
			if (sw->routing_table[i_dest->switch_id].out_link ==
			    NONE)
				sw->routing_table[i_dest->switch_id].out_link =
				    get_phys_connection(sw, next_switch);

			prev = i_dest;
			i_dest = i_dest->next;
		}

		CL_ASSERT(prev->next == NULL);
		prev->next = concat_dest;
		concat_dest = dest;
	}

	i_dest = (reachable_dest_t *) malloc(sizeof(reachable_dest_t));
	if (!i_dest)
		return -1;
	i_dest->switch_id = sw->id;
	i_dest->next = concat_dest;
	*destinations = i_dest;
	return 0;
}