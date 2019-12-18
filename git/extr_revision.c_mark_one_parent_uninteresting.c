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
struct commit_stack {int dummy; } ;
struct commit_list {int /*<<< orphan*/  item; struct commit_list* next; } ;
struct TYPE_2__ {int flags; } ;
struct commit {struct commit_list* parents; TYPE_1__ object; } ;

/* Variables and functions */
 int UNINTERESTING ; 
 int /*<<< orphan*/  commit_stack_push (struct commit_stack*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mark_one_parent_uninteresting(struct commit *commit,
					  struct commit_stack *pending)
{
	struct commit_list *l;

	if (commit->object.flags & UNINTERESTING)
		return;
	commit->object.flags |= UNINTERESTING;

	/*
	 * Normally we haven't parsed the parent
	 * yet, so we won't have a parent of a parent
	 * here. However, it may turn out that we've
	 * reached this commit some other way (where it
	 * wasn't uninteresting), in which case we need
	 * to mark its parents recursively too..
	 */
	for (l = commit->parents; l; l = l->next)
		commit_stack_push(pending, l->item);
}