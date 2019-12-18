#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* routing_table; } ;
typedef  TYPE_3__ switch_t ;
struct TYPE_12__ {int num_switches; TYPE_5__**** cdg_vertex_matrix; TYPE_3__** switches; } ;
typedef  TYPE_4__ lash_t ;
struct TYPE_13__ {int temp; int num_temp_depend; int num_deps; TYPE_1__* deps; int /*<<< orphan*/  num_using_vertex; } ;
typedef  TYPE_5__ cdg_vertex_t ;
struct TYPE_10__ {int out_link; } ;
struct TYPE_9__ {scalar_t__ num_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (int) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int get_next_switch (TYPE_4__*,int,int) ; 

__attribute__((used)) static void remove_temp_depend_for_sp(lash_t * p_lash, int sw, int dest_switch,
				      int lane)
{
	switch_t **switches = p_lash->switches;
	cdg_vertex_t ****cdg_vertex_matrix = p_lash->cdg_vertex_matrix;
	int next_switch, output_link, i;
	cdg_vertex_t *v;

	output_link = switches[sw]->routing_table[dest_switch].out_link;
	next_switch = get_next_switch(p_lash, sw, output_link);

	while (sw != dest_switch) {
		v = cdg_vertex_matrix[lane][sw][next_switch];
		CL_ASSERT(v != NULL);

		if (v->temp == 1) {
			cdg_vertex_matrix[lane][sw][next_switch] = NULL;
			free(v);
		} else {
			CL_ASSERT(v->num_temp_depend <= v->num_deps);
			v->num_deps = v->num_deps - v->num_temp_depend;
			v->num_temp_depend = 0;
			v->num_using_vertex--;

			for (i = v->num_deps; i < p_lash->num_switches - 1; i++)
				v->deps[i].num_used = 0;
		}

		sw = next_switch;
		output_link = switches[sw]->routing_table[dest_switch].out_link;

		if (sw != dest_switch)
			next_switch = get_next_switch(p_lash, sw, output_link);

	}
}