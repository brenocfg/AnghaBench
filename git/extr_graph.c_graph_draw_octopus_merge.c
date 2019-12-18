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
struct git_graph {int const num_parents; int num_new_columns; int num_columns; int const commit_index; int /*<<< orphan*/ * new_columns; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_write_column (struct strbuf*,int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static int graph_draw_octopus_merge(struct git_graph *graph,
				    struct strbuf *sb)
{
	/*
	 * Here dashless_parents represents the number of parents which don't
	 * need to have dashes (the edges labeled "0" and "1").  And
	 * dashful_parents are the remaining ones.
	 *
	 * | *---.
	 * | |\ \ \
	 * | | | | |
	 * x 0 1 2 3
	 *
	 */
	const int dashless_parents = 2;
	int dashful_parents = graph->num_parents - dashless_parents;

	/*
	 * Usually, we add one new column for each parent (like the diagram
	 * above) but sometimes the first parent goes into an existing column,
	 * like this:
	 *
	 * | *---.
	 * | |\ \ \
	 * |/ / / /
	 * x 0 1 2
	 *
	 * In which case the number of parents will be one greater than the
	 * number of added columns.
	 */
	int added_cols = (graph->num_new_columns - graph->num_columns);
	int parent_in_old_cols = graph->num_parents - added_cols;

	/*
	 * In both cases, commit_index corresponds to the edge labeled "0".
	 */
	int first_col = graph->commit_index + dashless_parents
	    - parent_in_old_cols;

	int i;
	for (i = 0; i < dashful_parents; i++) {
		strbuf_write_column(sb, &graph->new_columns[i+first_col], '-');
		strbuf_write_column(sb, &graph->new_columns[i+first_col],
				    i == dashful_parents-1 ? '.' : '-');
	}
	return 2 * dashful_parents;
}