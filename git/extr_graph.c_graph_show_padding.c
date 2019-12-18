#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct git_graph {TYPE_2__* revs; } ;
struct TYPE_3__ {int /*<<< orphan*/  file; } ;
struct TYPE_4__ {TYPE_1__ diffopt; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  default_diffopt ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  graph_padding_line (struct git_graph*,struct strbuf*) ; 
 int /*<<< orphan*/  graph_show_line_prefix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

void graph_show_padding(struct git_graph *graph)
{
	struct strbuf msgbuf = STRBUF_INIT;

	graph_show_line_prefix(default_diffopt);

	if (!graph)
		return;

	graph_padding_line(graph, &msgbuf);
	fwrite(msgbuf.buf, sizeof(char), msgbuf.len, graph->revs->diffopt.file);
	strbuf_release(&msgbuf);
}