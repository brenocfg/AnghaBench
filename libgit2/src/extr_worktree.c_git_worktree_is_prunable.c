#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  popts ;
struct TYPE_12__ {int flags; } ;
typedef  TYPE_1__ git_worktree_prune_options ;
typedef  int /*<<< orphan*/  git_worktree ;
struct TYPE_13__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_VERSION (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GIT_ERROR_WORKTREE ; 
 int GIT_WORKTREE_PRUNE_LOCKED ; 
 TYPE_1__ GIT_WORKTREE_PRUNE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_WORKTREE_PRUNE_OPTIONS_VERSION ; 
 int GIT_WORKTREE_PRUNE_VALID ; 
 int /*<<< orphan*/  git_buf_attach_notowned (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ git_worktree_is_locked (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ git_worktree_validate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

int git_worktree_is_prunable(git_worktree *wt,
	git_worktree_prune_options *opts)
{
	git_buf reason = GIT_BUF_INIT;
	git_worktree_prune_options popts = GIT_WORKTREE_PRUNE_OPTIONS_INIT;

	GIT_ERROR_CHECK_VERSION(
		opts, GIT_WORKTREE_PRUNE_OPTIONS_VERSION,
		"git_worktree_prune_options");

	if (opts)
		memcpy(&popts, opts, sizeof(popts));

	if ((popts.flags & GIT_WORKTREE_PRUNE_LOCKED) == 0 &&
		git_worktree_is_locked(&reason, wt))
	{
		if (!reason.size)
			git_buf_attach_notowned(&reason, "no reason given", 15);
		git_error_set(GIT_ERROR_WORKTREE, "not pruning locked working tree: '%s'", reason.ptr);
		git_buf_dispose(&reason);

		return 0;
	}

	if ((popts.flags & GIT_WORKTREE_PRUNE_VALID) == 0 &&
		git_worktree_validate(wt) == 0)
	{
		git_error_set(GIT_ERROR_WORKTREE, "not pruning valid working tree");
		return 0;
	}

	return 1;
}