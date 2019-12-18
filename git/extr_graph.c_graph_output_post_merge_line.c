#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct strbuf {int dummy; } ;
struct git_graph {int num_columns; int num_parents; struct commit* commit; struct commit_list* columns; } ;
struct commit_list {int /*<<< orphan*/  item; struct commit* commit; } ;
struct commit {int dummy; } ;
struct column {int /*<<< orphan*/  item; struct commit* commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRAPH_COLLAPSING ; 
 int /*<<< orphan*/  GRAPH_PADDING ; 
 int /*<<< orphan*/  assert (struct commit_list*) ; 
 struct commit_list* find_new_column_by_commit (struct git_graph*,int /*<<< orphan*/ ) ; 
 struct commit_list* first_interesting_parent (struct git_graph*) ; 
 scalar_t__ graph_is_mapping_correct (struct git_graph*) ; 
 int /*<<< orphan*/  graph_pad_horizontally (struct git_graph*,struct strbuf*,int) ; 
 int /*<<< orphan*/  graph_update_state (struct git_graph*,int /*<<< orphan*/ ) ; 
 struct commit_list* next_interesting_parent (struct git_graph*,struct commit_list*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_write_column (struct strbuf*,struct commit_list*,char) ; 

__attribute__((used)) static void graph_output_post_merge_line(struct git_graph *graph, struct strbuf *sb)
{
	int seen_this = 0;
	int i, j, chars_written;

	/*
	 * Output the post-merge row
	 */
	chars_written = 0;
	for (i = 0; i <= graph->num_columns; i++) {
		struct column *col = &graph->columns[i];
		struct commit *col_commit;
		if (i == graph->num_columns) {
			if (seen_this)
				break;
			col_commit = graph->commit;
		} else {
			col_commit = col->commit;
		}

		if (col_commit == graph->commit) {
			/*
			 * Since the current commit is a merge find
			 * the columns for the parent commits in
			 * new_columns and use those to format the
			 * edges.
			 */
			struct commit_list *parents = NULL;
			struct column *par_column;
			seen_this = 1;
			parents = first_interesting_parent(graph);
			assert(parents);
			par_column = find_new_column_by_commit(graph, parents->item);
			assert(par_column);

			strbuf_write_column(sb, par_column, '|');
			chars_written++;
			for (j = 0; j < graph->num_parents - 1; j++) {
				parents = next_interesting_parent(graph, parents);
				assert(parents);
				par_column = find_new_column_by_commit(graph, parents->item);
				assert(par_column);
				strbuf_write_column(sb, par_column, '\\');
				strbuf_addch(sb, ' ');
			}
			chars_written += j * 2;
		} else if (seen_this) {
			strbuf_write_column(sb, col, '\\');
			strbuf_addch(sb, ' ');
			chars_written += 2;
		} else {
			strbuf_write_column(sb, col, '|');
			strbuf_addch(sb, ' ');
			chars_written += 2;
		}
	}

	graph_pad_horizontally(graph, sb, chars_written);

	/*
	 * Update graph->state
	 */
	if (graph_is_mapping_correct(graph))
		graph_update_state(graph, GRAPH_PADDING);
	else
		graph_update_state(graph, GRAPH_COLLAPSING);
}