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
struct git_graph {int num_columns; int num_new_columns; int num_parents; int mapping_size; int* mapping; int commit_index; struct commit* commit; TYPE_1__* columns; int /*<<< orphan*/  new_columns; } ;
struct commit_list {struct commit* item; } ;
struct commit {int dummy; } ;
struct TYPE_2__ {struct commit* commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct commit_list* first_interesting_parent (struct git_graph*) ; 
 int /*<<< orphan*/  graph_ensure_capacity (struct git_graph*,int) ; 
 int /*<<< orphan*/  graph_increment_column_color (struct git_graph*) ; 
 int /*<<< orphan*/  graph_insert_into_new_columns (struct git_graph*,struct commit*,int*) ; 
 int /*<<< orphan*/  graph_update_width (struct git_graph*,int) ; 
 struct commit_list* next_interesting_parent (struct git_graph*,struct commit_list*) ; 

__attribute__((used)) static void graph_update_columns(struct git_graph *graph)
{
	struct commit_list *parent;
	int max_new_columns;
	int mapping_idx;
	int i, seen_this, is_commit_in_columns;

	/*
	 * Swap graph->columns with graph->new_columns
	 * graph->columns contains the state for the previous commit,
	 * and new_columns now contains the state for our commit.
	 *
	 * We'll re-use the old columns array as storage to compute the new
	 * columns list for the commit after this one.
	 */
	SWAP(graph->columns, graph->new_columns);
	graph->num_columns = graph->num_new_columns;
	graph->num_new_columns = 0;

	/*
	 * Now update new_columns and mapping with the information for the
	 * commit after this one.
	 *
	 * First, make sure we have enough room.  At most, there will
	 * be graph->num_columns + graph->num_parents columns for the next
	 * commit.
	 */
	max_new_columns = graph->num_columns + graph->num_parents;
	graph_ensure_capacity(graph, max_new_columns);

	/*
	 * Clear out graph->mapping
	 */
	graph->mapping_size = 2 * max_new_columns;
	for (i = 0; i < graph->mapping_size; i++)
		graph->mapping[i] = -1;

	/*
	 * Populate graph->new_columns and graph->mapping
	 *
	 * Some of the parents of this commit may already be in
	 * graph->columns.  If so, graph->new_columns should only contain a
	 * single entry for each such commit.  graph->mapping should
	 * contain information about where each current branch line is
	 * supposed to end up after the collapsing is performed.
	 */
	seen_this = 0;
	mapping_idx = 0;
	is_commit_in_columns = 1;
	for (i = 0; i <= graph->num_columns; i++) {
		struct commit *col_commit;
		if (i == graph->num_columns) {
			if (seen_this)
				break;
			is_commit_in_columns = 0;
			col_commit = graph->commit;
		} else {
			col_commit = graph->columns[i].commit;
		}

		if (col_commit == graph->commit) {
			int old_mapping_idx = mapping_idx;
			seen_this = 1;
			graph->commit_index = i;
			for (parent = first_interesting_parent(graph);
			     parent;
			     parent = next_interesting_parent(graph, parent)) {
				/*
				 * If this is a merge, or the start of a new
				 * childless column, increment the current
				 * color.
				 */
				if (graph->num_parents > 1 ||
				    !is_commit_in_columns) {
					graph_increment_column_color(graph);
				}
				graph_insert_into_new_columns(graph,
							      parent->item,
							      &mapping_idx);
			}
			/*
			 * We always need to increment mapping_idx by at
			 * least 2, even if it has no interesting parents.
			 * The current commit always takes up at least 2
			 * spaces.
			 */
			if (mapping_idx == old_mapping_idx)
				mapping_idx += 2;
		} else {
			graph_insert_into_new_columns(graph, col_commit,
						      &mapping_idx);
		}
	}

	/*
	 * Shrink mapping_size to be the minimum necessary
	 */
	while (graph->mapping_size > 1 &&
	       graph->mapping[graph->mapping_size - 1] < 0)
		graph->mapping_size--;

	/*
	 * Compute graph->width for this commit
	 */
	graph_update_width(graph, is_commit_in_columns);
}