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
struct TYPE_8__ {TYPE_1__* routing_table; } ;
typedef  TYPE_2__ switch_t ;
struct TYPE_9__ {TYPE_4__**** cdg_vertex_matrix; TYPE_2__** switches; } ;
typedef  TYPE_3__ lash_t ;
struct TYPE_10__ {int temp; scalar_t__ num_temp_depend; } ;
typedef  TYPE_4__ cdg_vertex_t ;
struct TYPE_7__ {int out_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (int /*<<< orphan*/ ) ; 
 int get_next_switch (TYPE_3__*,int,int) ; 

__attribute__((used)) static void set_temp_depend_to_permanent_for_sp(lash_t * p_lash, int sw,
						int dest_switch, int lane)
{
	switch_t **switches = p_lash->switches;
	cdg_vertex_t ****cdg_vertex_matrix = p_lash->cdg_vertex_matrix;
	int next_switch, output_link;
	cdg_vertex_t *v;

	output_link = switches[sw]->routing_table[dest_switch].out_link;
	next_switch = get_next_switch(p_lash, sw, output_link);

	while (sw != dest_switch) {
		v = cdg_vertex_matrix[lane][sw][next_switch];
		CL_ASSERT(v != NULL);

		if (v->temp == 1)
			v->temp = 0;
		else
			v->num_temp_depend = 0;

		sw = next_switch;
		output_link = switches[sw]->routing_table[dest_switch].out_link;

		if (sw != dest_switch)
			next_switch = get_next_switch(p_lash, sw, output_link);
	}

}