#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ locked; int /*<<< orphan*/  gitdir_path; } ;
typedef  TYPE_1__ git_worktree ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 scalar_t__ git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_worktree_is_locked (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ p_unlink (int /*<<< orphan*/ ) ; 

int git_worktree_unlock(git_worktree *wt)
{
	git_buf path = GIT_BUF_INIT;

	assert(wt);

	if (!git_worktree_is_locked(NULL, wt))
		return 1;

	if (git_buf_joinpath(&path, wt->gitdir_path, "locked") < 0)
		return -1;

	if (p_unlink(path.ptr) != 0) {
		git_buf_dispose(&path);
		return -1;
	}

	wt->locked = 0;

	git_buf_dispose(&path);

	return 0;
}