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
struct TYPE_12__ {unsigned int num_switches; TYPE_5__**** cdg_vertex_matrix; TYPE_3__** switches; } ;
typedef  TYPE_4__ lash_t ;
struct TYPE_13__ {int from; int to; int temp; int num_deps; int /*<<< orphan*/  num_temp_depend; TYPE_1__* deps; int /*<<< orphan*/  num_using_vertex; } ;
typedef  TYPE_5__ cdg_vertex_t ;
struct TYPE_10__ {int out_link; } ;
struct TYPE_9__ {int /*<<< orphan*/  num_used; TYPE_5__* v; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (int) ; 
 int NONE ; 
 TYPE_5__* calloc (int,int) ; 
 int get_next_switch (TYPE_4__*,int,int) ; 

__attribute__((used)) static int generate_cdg_for_sp(lash_t * p_lash, int sw, int dest_switch,
			       int lane)
{
	unsigned num_switches = p_lash->num_switches;
	switch_t **switches = p_lash->switches;
	cdg_vertex_t ****cdg_vertex_matrix = p_lash->cdg_vertex_matrix;
	int next_switch, output_link, j, exists;
	cdg_vertex_t *v, *prev = NULL;

	output_link = switches[sw]->routing_table[dest_switch].out_link;
	next_switch = get_next_switch(p_lash, sw, output_link);

	while (sw != dest_switch) {

		if (cdg_vertex_matrix[lane][sw][next_switch] == NULL) {
			v = calloc(1, sizeof(*v) + (num_switches - 1) * sizeof(v->deps[0]));
			if (!v)
				return -1;
			v->from = sw;
			v->to = next_switch;
			v->temp = 1;
			cdg_vertex_matrix[lane][sw][next_switch] = v;
		} else
			v = cdg_vertex_matrix[lane][sw][next_switch];

		v->num_using_vertex++;

		if (prev != NULL) {
			exists = 0;

			for (j = 0; j < prev->num_deps; j++)
				if (prev->deps[j].v == v) {
					exists = 1;
					prev->deps[j].num_used++;
				}

			if (exists == 0) {
				prev->deps[prev->num_deps].v = v;
				prev->deps[prev->num_deps].num_used++;
				prev->num_deps++;

				CL_ASSERT(prev->num_deps < (int)num_switches);

				if (prev->temp == 0)
					prev->num_temp_depend++;

			}
		}

		sw = next_switch;
		output_link = switches[sw]->routing_table[dest_switch].out_link;

		if (sw != dest_switch) {
			CL_ASSERT(output_link != NONE);
			next_switch = get_next_switch(p_lash, sw, output_link);
		}

		prev = v;
	}
	return 0;
}