#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  popts ;
struct TYPE_16__ {int flags; } ;
typedef  TYPE_1__ git_worktree_prune_options ;
struct TYPE_17__ {int /*<<< orphan*/  gitlink_path; int /*<<< orphan*/  name; int /*<<< orphan*/  commondir_path; } ;
typedef  TYPE_2__ git_worktree ;
struct TYPE_18__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_VERSION (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GIT_ERROR_WORKTREE ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 TYPE_1__ GIT_WORKTREE_PRUNE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_WORKTREE_PRUNE_OPTIONS_VERSION ; 
 int GIT_WORKTREE_PRUNE_WORKING_TREE ; 
 int /*<<< orphan*/  git_buf_attach (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int git_buf_printf (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int git_futils_rmdir_r (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* git_path_dirname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_worktree_is_prunable (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

int git_worktree_prune(git_worktree *wt,
	git_worktree_prune_options *opts)
{
	git_worktree_prune_options popts = GIT_WORKTREE_PRUNE_OPTIONS_INIT;
	git_buf path = GIT_BUF_INIT;
	char *wtpath;
	int err;

	GIT_ERROR_CHECK_VERSION(
		opts, GIT_WORKTREE_PRUNE_OPTIONS_VERSION,
		"git_worktree_prune_options");

	if (opts)
		memcpy(&popts, opts, sizeof(popts));

	if (!git_worktree_is_prunable(wt, &popts)) {
		err = -1;
		goto out;
	}

	/* Delete gitdir in parent repository */
	if ((err = git_buf_printf(&path, "%s/worktrees/%s", wt->commondir_path, wt->name)) < 0)
		goto out;
	if (!git_path_exists(path.ptr))
	{
		git_error_set(GIT_ERROR_WORKTREE, "worktree gitdir '%s' does not exist", path.ptr);
		err = -1;
		goto out;
	}
	if ((err = git_futils_rmdir_r(path.ptr, NULL, GIT_RMDIR_REMOVE_FILES)) < 0)
		goto out;

	/* Skip deletion of the actual working tree if it does
	 * not exist or deletion was not requested */
	if ((popts.flags & GIT_WORKTREE_PRUNE_WORKING_TREE) == 0 ||
		!git_path_exists(wt->gitlink_path))
	{
		goto out;
	}

	if ((wtpath = git_path_dirname(wt->gitlink_path)) == NULL)
		goto out;
	git_buf_attach(&path, wtpath, 0);
	if (!git_path_exists(path.ptr))
	{
		git_error_set(GIT_ERROR_WORKTREE, "working tree '%s' does not exist", path.ptr);
		err = -1;
		goto out;
	}
	if ((err = git_futils_rmdir_r(path.ptr, NULL, GIT_RMDIR_REMOVE_FILES)) < 0)
		goto out;

out:
	git_buf_dispose(&path);

	return err;
}