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
struct git_graph {TYPE_2__* revs; } ;
struct TYPE_3__ {int flags; } ;
struct commit {TYPE_1__ object; } ;
struct TYPE_4__ {scalar_t__ boundary; } ;

/* Variables and functions */
 int CHILD_SHOWN ; 
 scalar_t__ commit_show ; 
 scalar_t__ get_commit_action (TYPE_2__*,struct commit*) ; 

__attribute__((used)) static int graph_is_interesting(struct git_graph *graph, struct commit *commit)
{
	/*
	 * If revs->boundary is set, commits whose children have
	 * been shown are always interesting, even if they have the
	 * UNINTERESTING or TREESAME flags set.
	 */
	if (graph->revs && graph->revs->boundary) {
		if (commit->object.flags & CHILD_SHOWN)
			return 1;
	}

	/*
	 * Otherwise, use get_commit_action() to see if this commit is
	 * interesting
	 */
	return get_commit_action(graph->revs, commit) == commit_show;
}