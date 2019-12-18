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
struct worktree {int /*<<< orphan*/  path; int /*<<< orphan*/  is_detached; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_worktrees (struct worktree**) ; 
 struct worktree** get_worktrees (int /*<<< orphan*/ ) ; 
 scalar_t__ is_worktree_being_bisected (struct worktree*,char const*) ; 
 scalar_t__ is_worktree_being_rebased (struct worktree*,char const*) ; 

__attribute__((used)) static void reject_rebase_or_bisect_branch(const char *target)
{
	struct worktree **worktrees = get_worktrees(0);
	int i;

	for (i = 0; worktrees[i]; i++) {
		struct worktree *wt = worktrees[i];

		if (!wt->is_detached)
			continue;

		if (is_worktree_being_rebased(wt, target))
			die(_("Branch %s is being rebased at %s"),
			    target, wt->path);

		if (is_worktree_being_bisected(wt, target))
			die(_("Branch %s is being bisected at %s"),
			    target, wt->path);
	}

	free_worktrees(worktrees);
}