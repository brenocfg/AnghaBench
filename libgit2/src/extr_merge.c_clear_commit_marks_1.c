#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int flags; unsigned int out_degree; struct TYPE_4__** parents; } ;
typedef  TYPE_1__ git_commit_list_node ;
typedef  int /*<<< orphan*/  git_commit_list ;

/* Variables and functions */
 int /*<<< orphan*/ * git_commit_list_insert (TYPE_1__*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int clear_commit_marks_1(git_commit_list **plist,
		git_commit_list_node *commit, unsigned int mark)
{
	while (commit) {
		unsigned int i;

		if (!(mark & commit->flags))
			return 0;

		commit->flags &= ~mark;

		for (i = 1; i < commit->out_degree; i++) {
			git_commit_list_node *p = commit->parents[i];
			if (git_commit_list_insert(p, plist) == NULL)
				return -1;
		}

		commit = commit->out_degree ? commit->parents[0] : NULL;
	}

	return 0;
}