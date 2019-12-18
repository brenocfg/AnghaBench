#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned short out_degree; int uninteresting; struct TYPE_5__** parents; } ;
typedef  TYPE_1__ git_commit_list_node ;
typedef  int /*<<< orphan*/  git_commit_list ;

/* Variables and functions */
 int /*<<< orphan*/  git_commit_list_insert (TYPE_1__*,int /*<<< orphan*/ **) ; 
 TYPE_1__* git_commit_list_pop (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void mark_parents_uninteresting(git_commit_list_node *commit)
{
	unsigned short i;
	git_commit_list *parents = NULL;

	for (i = 0; i < commit->out_degree; i++)
		git_commit_list_insert(commit->parents[i], &parents);


	while (parents) {
		commit = git_commit_list_pop(&parents);

		while (commit) {
			if (commit->uninteresting)
				break;

			commit->uninteresting = 1;
			/*
			 * If we've reached this commit some other way
			 * already, we need to mark its parents uninteresting
			 * as well.
			 */
			if (!commit->parents)
				break;

			for (i = 0; i < commit->out_degree; i++)
				git_commit_list_insert(commit->parents[i], &parents);
			commit = commit->parents[0];
		}
	}
}