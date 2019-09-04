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
struct TYPE_4__ {int /*<<< orphan*/  limited; } ;
typedef  TYPE_1__ git_revwalk ;
typedef  int /*<<< orphan*/  git_commit_list_node ;
typedef  int /*<<< orphan*/  git_commit_list ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int add_parents_to_list (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * git_commit_list_pop (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_error_clear () ; 

__attribute__((used)) static int get_revision(git_commit_list_node **out, git_revwalk *walk, git_commit_list **list)
{
	int error;
	git_commit_list_node *commit;

	commit = git_commit_list_pop(list);
	if (!commit) {
		git_error_clear();
		return GIT_ITEROVER;
	}

	/*
	 * If we did not run limit_list and we must add parents to the
	 * list ourselves.
	 */
	if (!walk->limited) {
		if ((error = add_parents_to_list(walk, commit, list)) < 0)
			return error;
	}

	*out = commit;
	return 0;
}