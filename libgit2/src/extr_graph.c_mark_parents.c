#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_pqueue ;
struct TYPE_8__ {unsigned int flags; unsigned int out_degree; struct TYPE_8__** parents; } ;
typedef  TYPE_1__ git_commit_list_node ;
typedef  int /*<<< orphan*/  git_commit_list ;

/* Variables and functions */
 unsigned int PARENT1 ; 
 unsigned int PARENT2 ; 
 unsigned int RESULT ; 
 unsigned int STALE ; 
 int /*<<< orphan*/  git_commit_list_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * git_commit_list_insert (TYPE_1__*,int /*<<< orphan*/ **) ; 
 scalar_t__ git_commit_list_parse (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_commit_list_time_cmp ; 
 int /*<<< orphan*/  git_pqueue_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_pqueue_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ git_pqueue_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* git_pqueue_pop (int /*<<< orphan*/ *) ; 
 scalar_t__ interesting (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mark_parents(git_revwalk *walk, git_commit_list_node *one,
	git_commit_list_node *two)
{
	unsigned int i;
	git_commit_list *roots = NULL;
	git_pqueue list;

	/* if the commit is repeated, we have a our merge base already */
	if (one == two) {
		one->flags |= PARENT1 | PARENT2 | RESULT;
		return 0;
	}

	if (git_pqueue_init(&list, 0, 2, git_commit_list_time_cmp) < 0)
		return -1;

	if (git_commit_list_parse(walk, one) < 0)
		goto on_error;
	one->flags |= PARENT1;
	if (git_pqueue_insert(&list, one) < 0)
		goto on_error;

	if (git_commit_list_parse(walk, two) < 0)
		goto on_error;
	two->flags |= PARENT2;
	if (git_pqueue_insert(&list, two) < 0)
		goto on_error;

	/* as long as there are non-STALE commits */
	while (interesting(&list, roots)) {
		git_commit_list_node *commit = git_pqueue_pop(&list);
		unsigned int flags;

		if (commit == NULL)
			break;

		flags = commit->flags & (PARENT1 | PARENT2 | STALE);
		if (flags == (PARENT1 | PARENT2)) {
			if (!(commit->flags & RESULT))
				commit->flags |= RESULT;
			/* we mark the parents of a merge stale */
			flags |= STALE;
		}

		for (i = 0; i < commit->out_degree; i++) {
			git_commit_list_node *p = commit->parents[i];
			if ((p->flags & flags) == flags)
				continue;

			if (git_commit_list_parse(walk, p) < 0)
				goto on_error;

			p->flags |= flags;
			if (git_pqueue_insert(&list, p) < 0)
				goto on_error;
		}

		/* Keep track of root commits, to make sure the path gets marked */
		if (commit->out_degree == 0) {
			if (git_commit_list_insert(commit, &roots) == NULL)
				goto on_error;
		}
	}

	git_commit_list_free(&roots);
	git_pqueue_free(&list);
	return 0;

on_error:
	git_commit_list_free(&roots);
	git_pqueue_free(&list);
	return -1;
}