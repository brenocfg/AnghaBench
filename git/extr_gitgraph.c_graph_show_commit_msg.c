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
struct strbuf {int len; char* buf; } ;
struct git_graph {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  graph_is_commit_finished (struct git_graph*) ; 
 int /*<<< orphan*/  graph_show_remainder (struct git_graph*) ; 
 int /*<<< orphan*/  graph_show_strbuf (struct git_graph*,int /*<<< orphan*/ *,struct strbuf const*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 

void graph_show_commit_msg(struct git_graph *graph,
			   FILE *file,
			   struct strbuf const *sb)
{
	int newline_terminated;

	/*
	 * Show the commit message
	 */
	graph_show_strbuf(graph, file, sb);

	if (!graph)
		return;

	newline_terminated = (sb->len && sb->buf[sb->len - 1] == '\n');

	/*
	 * If there is more output needed for this commit, show it now
	 */
	if (!graph_is_commit_finished(graph)) {
		/*
		 * If sb doesn't have a terminating newline, print one now,
		 * so we can start the remainder of the graph output on a
		 * new line.
		 */
		if (!newline_terminated)
			putc('\n', file);

		graph_show_remainder(graph);

		/*
		 * If sb ends with a newline, our output should too.
		 */
		if (newline_terminated)
			putc('\n', file);
	}
}