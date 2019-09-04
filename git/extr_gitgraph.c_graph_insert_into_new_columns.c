#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct git_graph {int num_new_columns; int* mapping; TYPE_1__* new_columns; } ;
struct commit {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  color; struct commit* commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  graph_find_commit_color (struct git_graph*,struct commit*) ; 

__attribute__((used)) static void graph_insert_into_new_columns(struct git_graph *graph,
					  struct commit *commit,
					  int *mapping_index)
{
	int i;

	/*
	 * If the commit is already in the new_columns list, we don't need to
	 * add it.  Just update the mapping correctly.
	 */
	for (i = 0; i < graph->num_new_columns; i++) {
		if (graph->new_columns[i].commit == commit) {
			graph->mapping[*mapping_index] = i;
			*mapping_index += 2;
			return;
		}
	}

	/*
	 * This commit isn't already in new_columns.  Add it.
	 */
	graph->new_columns[graph->num_new_columns].commit = commit;
	graph->new_columns[graph->num_new_columns].color = graph_find_commit_color(graph, commit);
	graph->mapping[*mapping_index] = graph->num_new_columns;
	*mapping_index += 2;
	graph->num_new_columns++;
}