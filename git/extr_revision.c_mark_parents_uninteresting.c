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
struct commit_stack {scalar_t__ nr; } ;
struct commit_list {int /*<<< orphan*/  item; struct commit_list* next; } ;
struct commit {struct commit_list* parents; } ;

/* Variables and functions */
 struct commit_stack COMMIT_STACK_INIT ; 
 int /*<<< orphan*/  commit_stack_clear (struct commit_stack*) ; 
 int /*<<< orphan*/  commit_stack_pop (struct commit_stack*) ; 
 int /*<<< orphan*/  mark_one_parent_uninteresting (int /*<<< orphan*/ ,struct commit_stack*) ; 

void mark_parents_uninteresting(struct commit *commit)
{
	struct commit_stack pending = COMMIT_STACK_INIT;
	struct commit_list *l;

	for (l = commit->parents; l; l = l->next)
		mark_one_parent_uninteresting(l->item, &pending);

	while (pending.nr > 0)
		mark_one_parent_uninteresting(commit_stack_pop(&pending),
					      &pending);

	commit_stack_clear(&pending);
}