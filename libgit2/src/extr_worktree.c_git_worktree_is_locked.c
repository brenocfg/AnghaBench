#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  gitdir_path; } ;
typedef  TYPE_1__ git_worktree ;
struct TYPE_12__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int git_path_exists (int /*<<< orphan*/ ) ; 

int git_worktree_is_locked(git_buf *reason, const git_worktree *wt)
{
	git_buf path = GIT_BUF_INIT;
	int ret;

	assert(wt);

	if (reason)
		git_buf_clear(reason);

	if ((ret = git_buf_joinpath(&path, wt->gitdir_path, "locked")) < 0)
		goto out;
	if ((ret = git_path_exists(path.ptr)) && reason)
		git_futils_readbuffer(reason, path.ptr);

out:
	git_buf_dispose(&path);

	return ret;
}