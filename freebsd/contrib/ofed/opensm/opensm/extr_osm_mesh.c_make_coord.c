#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__* node; } ;
typedef  TYPE_4__ switch_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
struct TYPE_13__ {unsigned int dimension; } ;
typedef  TYPE_5__ mesh_t ;
struct TYPE_14__ {int num_switches; TYPE_4__** switches; TYPE_1__* p_osm; } ;
typedef  TYPE_6__ lash_t ;
struct TYPE_11__ {int* coord; unsigned int num_links; int* axes; TYPE_2__** links; } ;
struct TYPE_10__ {size_t switch_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int LARGE ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  OSM_LOG_DEBUG ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ *) ; 
 int* calloc (unsigned int,int) ; 
 scalar_t__ ltmag (int,int) ; 

__attribute__((used)) static int make_coord(lash_t *p_lash, mesh_t *mesh, int seed)
{
	osm_log_t *p_log = &p_lash->p_osm->log;
	unsigned int i, j, k;
	int sw;
	switch_t *s, *s1;
	unsigned int change;
	unsigned int dimension = mesh->dimension;
	int num_switches = p_lash->num_switches;
	int assigned_axes = 0, unassigned_axes = 0;

	OSM_LOG_ENTER(p_log);

	for (sw = 0; sw < num_switches; sw++) {
		s = p_lash->switches[sw];

		s->node->coord = calloc(dimension, sizeof(int));
		if (!s->node->coord) {
			OSM_LOG(p_log, OSM_LOG_ERROR,
				"Failed allocating coord - out of memory\n");
			OSM_LOG_EXIT(p_log);
			return -1;
		}

		for (i = 0; i < dimension; i++)
			s->node->coord[i] = (sw == seed) ? 0 : LARGE;

		for (i = 0; i < s->node->num_links; i++)
			if (s->node->axes[i] == 0)
				unassigned_axes++;
			else
				assigned_axes++;
	}

	OSM_LOG(p_log, OSM_LOG_DEBUG, "%d/%d unassigned/assigned axes\n",
		unassigned_axes, assigned_axes);

	do {
		change = 0;

		for (sw = 0; sw < num_switches; sw++) {
			s = p_lash->switches[sw];

			if (s->node->coord[0] == LARGE)
				continue;

			for (j = 0; j < s->node->num_links; j++) {
				if (!s->node->axes[j])
					continue;

				s1 = p_lash->switches[s->node->links[j]->switch_id];

				for (k = 0; k < dimension; k++) {
					int coord = s->node->coord[k];
					unsigned axis = s->node->axes[j] - 1;

					if (k == axis/2)
						coord += (axis & 1)? -1 : +1;

					if (ltmag(coord, s1->node->coord[k])) {
						s1->node->coord[k] = coord;
						change++;
					}
				}
			}
		}
	} while (change);

	OSM_LOG_EXIT(p_log);
	return 0;
}