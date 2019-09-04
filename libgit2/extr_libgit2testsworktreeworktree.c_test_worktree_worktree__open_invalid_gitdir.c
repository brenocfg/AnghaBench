#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_worktree ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;
struct TYPE_11__ {TYPE_2__* repo; } ;
struct TYPE_10__ {int /*<<< orphan*/  commondir; } ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_7__ fixture ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_futils_writebuffer (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_repository_open_from_worktree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_worktree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_worktree_lookup (int /*<<< orphan*/ **,TYPE_2__*,char*) ; 

void test_worktree_worktree__open_invalid_gitdir(void)
{
	git_worktree *wt;
	git_repository *repo;
	git_buf buf = GIT_BUF_INIT, path = GIT_BUF_INIT;

	cl_git_pass(git_buf_sets(&buf, "/path/to/nonexistent/gitdir"));
	cl_git_pass(git_buf_printf(&path,
		    "%s/worktrees/testrepo-worktree/gitdir",
		    fixture.repo->commondir));
	cl_git_pass(git_futils_writebuffer(&buf, path.ptr, O_RDWR, 0644));

	cl_git_pass(git_worktree_lookup(&wt, fixture.repo, "testrepo-worktree"));
	cl_git_fail(git_repository_open_from_worktree(&repo, wt));

	git_buf_dispose(&buf);
	git_buf_dispose(&path);
	git_worktree_free(wt);
}