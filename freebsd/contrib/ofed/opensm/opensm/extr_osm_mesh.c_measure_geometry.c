#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* node; } ;
typedef  TYPE_3__ switch_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
struct TYPE_11__ {int dimension; int* size; int* dim_order; } ;
typedef  TYPE_4__ mesh_t ;
struct TYPE_12__ {int num_switches; TYPE_3__** switches; TYPE_1__* p_osm; } ;
typedef  TYPE_5__ lash_t ;
struct TYPE_9__ {int* coord; } ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int LARGE ; 
 int MAX_DIMENSION ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ *) ; 
 int* calloc (int,int) ; 

__attribute__((used)) static int measure_geometry(lash_t *p_lash, mesh_t *mesh)
{
	osm_log_t *p_log = &p_lash->p_osm->log;
	int i, j;
	int sw;
	switch_t *s;
	int dimension = mesh->dimension;
	int num_switches = p_lash->num_switches;
	int max[MAX_DIMENSION];
	int min[MAX_DIMENSION];
	int size[MAX_DIMENSION];
	int max_size;
	int max_index;

	OSM_LOG_ENTER(p_log);

	mesh->size = calloc(dimension, sizeof(int));
	if (!mesh->size) {
		OSM_LOG(p_log, OSM_LOG_ERROR,
			"Failed allocating size - out of memory\n");
		OSM_LOG_EXIT(p_log);
		return -1;
	}

	for (i = 0; i < dimension; i++) {
		max[i] = -LARGE;
		min[i] = LARGE;
	}

	for (sw = 0; sw < num_switches; sw++) {
		s = p_lash->switches[sw];

		for (i = 0; i < dimension; i++) {
			if (s->node->coord[i] == LARGE)
				continue;
			if (s->node->coord[i] > max[i])
				max[i] = s->node->coord[i];
			if (s->node->coord[i] < min[i])
				min[i] = s->node->coord[i];
		}
	}

	for (i = 0; i < dimension; i++)
		mesh->size[i] = size[i] = max[i] - min[i] + 1;

	/*
	 * find an order of dimensions that places largest
	 * sizes first since this seems to work best with LASH
	 */
	for (j = 0; j < dimension; j++) {
		max_size = -1;
		max_index = -1;

		for (i = 0; i < dimension; i++) {
			if (size[i] > max_size) {
				max_size = size[i];
				max_index = i;
			}
		}

		mesh->dim_order[j] = max_index;
		size[max_index] = -1;
	}

	OSM_LOG_EXIT(p_log);
	return 0;
}