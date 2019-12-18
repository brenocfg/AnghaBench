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
struct git_graph {int state; } ;

/* Variables and functions */
#define  GRAPH_COLLAPSING 133 
#define  GRAPH_COMMIT 132 
#define  GRAPH_PADDING 131 
#define  GRAPH_POST_MERGE 130 
#define  GRAPH_PRE_COMMIT 129 
#define  GRAPH_SKIP 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  graph_output_collapsing_line (struct git_graph*,struct strbuf*) ; 
 int /*<<< orphan*/  graph_output_commit_line (struct git_graph*,struct strbuf*) ; 
 int /*<<< orphan*/  graph_output_padding_line (struct git_graph*,struct strbuf*) ; 
 int /*<<< orphan*/  graph_output_post_merge_line (struct git_graph*,struct strbuf*) ; 
 int /*<<< orphan*/  graph_output_pre_commit_line (struct git_graph*,struct strbuf*) ; 
 int /*<<< orphan*/  graph_output_skip_line (struct git_graph*,struct strbuf*) ; 

int graph_next_line(struct git_graph *graph, struct strbuf *sb)
{
	switch (graph->state) {
	case GRAPH_PADDING:
		graph_output_padding_line(graph, sb);
		return 0;
	case GRAPH_SKIP:
		graph_output_skip_line(graph, sb);
		return 0;
	case GRAPH_PRE_COMMIT:
		graph_output_pre_commit_line(graph, sb);
		return 0;
	case GRAPH_COMMIT:
		graph_output_commit_line(graph, sb);
		return 1;
	case GRAPH_POST_MERGE:
		graph_output_post_merge_line(graph, sb);
		return 0;
	case GRAPH_COLLAPSING:
		graph_output_collapsing_line(graph, sb);
		return 0;
	}

	assert(0);
	return 0;
}