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
struct git_graph {TYPE_1__* revs; } ;
struct commit_list {int /*<<< orphan*/  item; struct commit_list* next; } ;
struct TYPE_2__ {scalar_t__ first_parent_only; } ;

/* Variables and functions */
 scalar_t__ graph_is_interesting (struct git_graph*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct commit_list *next_interesting_parent(struct git_graph *graph,
						   struct commit_list *orig)
{
	struct commit_list *list;

	/*
	 * If revs->first_parent_only is set, only the first
	 * parent is interesting.  None of the others are.
	 */
	if (graph->revs->first_parent_only)
		return NULL;

	/*
	 * Return the next interesting commit after orig
	 */
	for (list = orig->next; list; list = list->next) {
		if (graph_is_interesting(graph, list->item))
			return list;
	}

	return NULL;
}