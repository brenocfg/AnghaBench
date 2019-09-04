#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int dummy; } ;
struct git_graph {TYPE_3__* commit; TYPE_2__* revs; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_6__ {TYPE_1__ object; } ;
struct TYPE_5__ {int /*<<< orphan*/  boundary; } ;

/* Variables and functions */
 int BOUNDARY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_revision_mark (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void graph_output_commit_char(struct git_graph *graph, struct strbuf *sb)
{
	/*
	 * For boundary commits, print 'o'
	 * (We should only see boundary commits when revs->boundary is set.)
	 */
	if (graph->commit->object.flags & BOUNDARY) {
		assert(graph->revs->boundary);
		strbuf_addch(sb, 'o');
		return;
	}

	/*
	 * get_revision_mark() handles all other cases without assert()
	 */
	strbuf_addstr(sb, get_revision_mark(graph->revs, graph->commit));
}