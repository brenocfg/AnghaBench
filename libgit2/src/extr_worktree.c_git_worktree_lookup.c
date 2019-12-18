#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_worktree ;
struct TYPE_8__ {int /*<<< orphan*/  commondir; } ;
typedef  TYPE_1__ git_repository ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_buf_printf (TYPE_2__*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_repository_workdir (TYPE_1__*) ; 
 int /*<<< orphan*/  git_worktree_free (int /*<<< orphan*/ *) ; 
 int open_worktree_dir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

int git_worktree_lookup(git_worktree **out, git_repository *repo, const char *name)
{
	git_buf path = GIT_BUF_INIT;
	git_worktree *wt = NULL;
	int error;

	assert(repo && name);

	*out = NULL;

	if ((error = git_buf_printf(&path, "%s/worktrees/%s", repo->commondir, name)) < 0)
		goto out;

	if ((error = (open_worktree_dir(out, git_repository_workdir(repo), path.ptr, name))) < 0)
		goto out;

out:
	git_buf_dispose(&path);

	if (error)
		git_worktree_free(wt);

	return error;
}