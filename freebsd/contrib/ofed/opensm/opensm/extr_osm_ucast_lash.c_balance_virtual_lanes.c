#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {unsigned int num_switches; int* num_mst_in_lane; int*** virtual_location; int balance_limit; TYPE_5__** switches; TYPE_3__* p_osm; TYPE_7__**** cdg_vertex_matrix; } ;
typedef  TYPE_6__ lash_t ;
struct TYPE_21__ {scalar_t__ seen; scalar_t__ visiting_number; } ;
typedef  TYPE_7__ cdg_vertex_t ;
struct TYPE_19__ {TYPE_4__* routing_table; } ;
struct TYPE_18__ {int out_link; int lane; } ;
struct TYPE_15__ {unsigned int lash_start_vl; } ;
struct TYPE_16__ {TYPE_1__ opt; } ;
struct TYPE_17__ {TYPE_2__ subn; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (int /*<<< orphan*/ ) ; 
 int MAX_INT ; 
 unsigned int abs (int /*<<< orphan*/ ) ; 
 int cycle_exists (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ generate_cdg_for_sp (TYPE_6__*,int,int,int) ; 
 int get_next_switch (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  rand () ; 
 int /*<<< orphan*/  remove_semipermanent_depend_for_sp (TYPE_6__*,int,int,int) ; 
 int /*<<< orphan*/  remove_temp_depend_for_sp (TYPE_6__*,int,int,int) ; 
 int /*<<< orphan*/  set_temp_depend_to_permanent_for_sp (TYPE_6__*,int,int,int) ; 

__attribute__((used)) static int balance_virtual_lanes(lash_t * p_lash, unsigned lanes_needed)
{
	unsigned num_switches = p_lash->num_switches;
	cdg_vertex_t ****cdg_vertex_matrix = p_lash->cdg_vertex_matrix;
	int *num_mst_in_lane = p_lash->num_mst_in_lane;
	int ***virtual_location = p_lash->virtual_location;
	int min_filled_lane, max_filled_lane, trials;
	int old_min_filled_lane, old_max_filled_lane, new_num_min_lane,
	    new_num_max_lane;
	unsigned int i, j;
	int src, dest, start, next_switch, output_link;
	int next_switch2, output_link2;
	int stop = 0, cycle_found;
	int cycle_found2;
	unsigned start_vl = p_lash->p_osm->subn.opt.lash_start_vl;

	max_filled_lane = 0;
	min_filled_lane = lanes_needed - 1;

	trials = num_mst_in_lane[max_filled_lane];
	if (lanes_needed == 1)
		stop = 1;

	while (stop == 0) {
		src = abs(rand()) % (num_switches);
		dest = abs(rand()) % (num_switches);

		while (virtual_location[src][dest][max_filled_lane] != 1) {
			start = dest;
			if (dest == num_switches - 1)
				dest = 0;
			else
				dest++;

			while (dest != start
			       && virtual_location[src][dest][max_filled_lane]
			       != 1) {
				if (dest == num_switches - 1)
					dest = 0;
				else
					dest++;
			}

			if (virtual_location[src][dest][max_filled_lane] != 1) {
				if (src == num_switches - 1)
					src = 0;
				else
					src++;
			}
		}

		if (generate_cdg_for_sp(p_lash, src, dest, min_filled_lane) ||
		    generate_cdg_for_sp(p_lash, dest, src, min_filled_lane))
			return -1;

		output_link = p_lash->switches[src]->routing_table[dest].out_link;
		next_switch = get_next_switch(p_lash, src, output_link);

		output_link2 = p_lash->switches[dest]->routing_table[src].out_link;
		next_switch2 = get_next_switch(p_lash, dest, output_link2);

		CL_ASSERT(cdg_vertex_matrix[min_filled_lane][src][next_switch] != NULL);
		CL_ASSERT(cdg_vertex_matrix[min_filled_lane][dest][next_switch2] != NULL);

		cycle_found =
		    cycle_exists(cdg_vertex_matrix[min_filled_lane][src][next_switch], NULL, NULL,
				 1);
		cycle_found2 =
		    cycle_exists(cdg_vertex_matrix[min_filled_lane][dest][next_switch2], NULL, NULL,
				 1);

		for (i = 0; i < num_switches; i++)
			for (j = 0; j < num_switches; j++)
				if (cdg_vertex_matrix[min_filled_lane][i][j] != NULL) {
					cdg_vertex_matrix[min_filled_lane][i][j]->visiting_number =
					    0;
					cdg_vertex_matrix[min_filled_lane][i][j]->seen = 0;
				}

		if (cycle_found == 1 || cycle_found2 == 1) {
			remove_temp_depend_for_sp(p_lash, src, dest, min_filled_lane);
			remove_temp_depend_for_sp(p_lash, dest, src, min_filled_lane);

			virtual_location[src][dest][max_filled_lane] = 2;
			virtual_location[dest][src][max_filled_lane] = 2;
			trials--;
			trials--;
		} else {
			set_temp_depend_to_permanent_for_sp(p_lash, src, dest, min_filled_lane);
			set_temp_depend_to_permanent_for_sp(p_lash, dest, src, min_filled_lane);

			num_mst_in_lane[max_filled_lane]--;
			num_mst_in_lane[max_filled_lane]--;
			num_mst_in_lane[min_filled_lane]++;
			num_mst_in_lane[min_filled_lane]++;

			remove_semipermanent_depend_for_sp(p_lash, src, dest, max_filled_lane);
			remove_semipermanent_depend_for_sp(p_lash, dest, src, max_filled_lane);
			virtual_location[src][dest][max_filled_lane] = 0;
			virtual_location[dest][src][max_filled_lane] = 0;
			virtual_location[src][dest][min_filled_lane] = 1;
			virtual_location[dest][src][min_filled_lane] = 1;
			p_lash->switches[src]->routing_table[dest].lane = min_filled_lane + start_vl;
			p_lash->switches[dest]->routing_table[src].lane = min_filled_lane + start_vl;
		}

		if (trials == 0)
			stop = 1;
		else {
			if (num_mst_in_lane[max_filled_lane] - num_mst_in_lane[min_filled_lane] <
			    p_lash->balance_limit)
				stop = 1;
		}

		old_min_filled_lane = min_filled_lane;
		old_max_filled_lane = max_filled_lane;

		new_num_min_lane = MAX_INT;
		new_num_max_lane = 0;

		for (i = 0; i < lanes_needed; i++) {

			if (num_mst_in_lane[i] < new_num_min_lane) {
				new_num_min_lane = num_mst_in_lane[i];
				min_filled_lane = i;
			}

			if (num_mst_in_lane[i] > new_num_max_lane) {
				new_num_max_lane = num_mst_in_lane[i];
				max_filled_lane = i;
			}
		}

		if (old_min_filled_lane != min_filled_lane) {
			trials = num_mst_in_lane[max_filled_lane];
			for (i = 0; i < num_switches; i++)
				for (j = 0; j < num_switches; j++)
					if (virtual_location[i][j][max_filled_lane] == 2)
						virtual_location[i][j][max_filled_lane] = 1;
		}

		if (old_max_filled_lane != max_filled_lane) {
			trials = num_mst_in_lane[max_filled_lane];
			for (i = 0; i < num_switches; i++)
				for (j = 0; j < num_switches; j++)
					if (virtual_location[i][j][old_max_filled_lane] == 2)
						virtual_location[i][j][old_max_filled_lane] = 1;
		}
	}
	return 0;
}