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
struct TYPE_10__ {TYPE_4__* node; } ;
typedef  TYPE_2__ switch_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
struct TYPE_11__ {int dimension; int* dim_order; } ;
typedef  TYPE_3__ mesh_t ;
struct TYPE_12__ {int num_links; scalar_t__* coord; int* axes; int /*<<< orphan*/ ** links; } ;
typedef  TYPE_4__ mesh_node_t ;
typedef  int /*<<< orphan*/  link_t ;
struct TYPE_13__ {TYPE_2__** switches; TYPE_1__* p_osm; } ;
typedef  TYPE_5__ lash_t ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 int opposite (TYPE_2__*,int) ; 

__attribute__((used)) static int reorder_node_links(lash_t *p_lash, mesh_t *mesh, int sw)
{
	osm_log_t *p_log = &p_lash->p_osm->log;
	switch_t *s = p_lash->switches[sw];
	mesh_node_t *node = s->node;
	int n = node->num_links;
	link_t **links;
	int *axes;
	int i, j, k, l;
	int c;
	int next = 0;
	int dimension = mesh->dimension;

	if (!(links = calloc(n, sizeof(link_t *)))) {
		OSM_LOG(p_log, OSM_LOG_ERROR,
			"Failed allocating links array - out of memory\n");
		return -1;
	}

	if (!(axes = calloc(n, sizeof(int)))) {
		free(links);
		OSM_LOG(p_log, OSM_LOG_ERROR,
			"Failed allocating axes array - out of memory\n");
		return -1;
	}

	/*
	 * find the links with axes
	 */
	for (i = 0; i < dimension; i++) {
		j = mesh->dim_order[i];
		for (k = 1; k <= 2; k++) {
			c = 2*j + k;

			if (node->coord[j] > 0)
				c = opposite(s, c);

			for (l = 0; l < n; l++) {
				if (!node->links[l])
					continue;
				if (node->axes[l] == c) {
					links[next] = node->links[l];
					axes[next] = node->axes[l];
					node->links[l] = NULL;
					next++;
				}
			}
		}
	}

	/*
	 * get the rest
	 */
	for (i = 0; i < n; i++) {
		if (!node->links[i])
			continue;

		links[next] = node->links[i];
		axes[next] = node->axes[i];
		node->links[i] = NULL;
		next++;
	}

	for (i = 0; i < n; i++) {
		node->links[i] = links[i];
		node->axes[i] = axes[i];
	}

	free(links);
	free(axes);

	return 0;
}