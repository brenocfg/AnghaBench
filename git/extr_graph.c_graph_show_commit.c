#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct git_graph {TYPE_1__* revs; } ;
struct TYPE_5__ {int /*<<< orphan*/  file; } ;
struct TYPE_4__ {TYPE_2__ diffopt; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 TYPE_2__* default_diffopt ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ graph_is_commit_finished (struct git_graph*) ; 
 int graph_next_line (struct git_graph*,struct strbuf*) ; 
 int /*<<< orphan*/  graph_show_line_prefix (TYPE_2__*) ; 
 int /*<<< orphan*/  graph_show_padding (struct git_graph*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int /*<<< orphan*/ ) ; 

void graph_show_commit(struct git_graph *graph)
{
	struct strbuf msgbuf = STRBUF_INIT;
	int shown_commit_line = 0;

	graph_show_line_prefix(default_diffopt);

	if (!graph)
		return;

	/*
	 * When showing a diff of a merge against each of its parents, we
	 * are called once for each parent without graph_update having been
	 * called.  In this case, simply output a single padding line.
	 */
	if (graph_is_commit_finished(graph)) {
		graph_show_padding(graph);
		shown_commit_line = 1;
	}

	while (!shown_commit_line && !graph_is_commit_finished(graph)) {
		shown_commit_line = graph_next_line(graph, &msgbuf);
		fwrite(msgbuf.buf, sizeof(char), msgbuf.len,
			graph->revs->diffopt.file);
		if (!shown_commit_line) {
			putc('\n', graph->revs->diffopt.file);
			graph_show_line_prefix(&graph->revs->diffopt);
		}
		strbuf_setlen(&msgbuf, 0);
	}

	strbuf_release(&msgbuf);
}