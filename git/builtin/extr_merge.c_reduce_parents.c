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
struct commit_list {int dummy; } ;
struct commit {int dummy; } ;
struct TYPE_2__ {struct commit_list* next; } ;

/* Variables and functions */
 TYPE_1__* commit_list_insert (struct commit*,struct commit_list**) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 struct commit* pop_commit (struct commit_list**) ; 
 struct commit_list* reduce_heads (struct commit_list*) ; 

__attribute__((used)) static struct commit_list *reduce_parents(struct commit *head_commit,
					  int *head_subsumed,
					  struct commit_list *remoteheads)
{
	struct commit_list *parents, **remotes;

	/*
	 * Is the current HEAD reachable from another commit being
	 * merged?  If so we do not want to record it as a parent of
	 * the resulting merge, unless --no-ff is given.  We will flip
	 * this variable to 0 when we find HEAD among the independent
	 * tips being merged.
	 */
	*head_subsumed = 1;

	/* Find what parents to record by checking independent ones. */
	parents = reduce_heads(remoteheads);
	free_commit_list(remoteheads);

	remoteheads = NULL;
	remotes = &remoteheads;
	while (parents) {
		struct commit *commit = pop_commit(&parents);
		if (commit == head_commit)
			*head_subsumed = 0;
		else
			remotes = &commit_list_insert(commit, remotes)->next;
	}
	return remoteheads;
}