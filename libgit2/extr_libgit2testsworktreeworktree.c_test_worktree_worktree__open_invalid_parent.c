#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_worktree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_4__ {int /*<<< orphan*/  repo; TYPE_1__* worktree; } ;
struct TYPE_3__ {int /*<<< orphan*/  gitlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_2__ fixture ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_sets (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_futils_writebuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_repository_open_from_worktree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_worktree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_worktree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 

void test_worktree_worktree__open_invalid_parent(void)
{
	git_worktree *wt;
	git_repository *repo;
	git_buf buf = GIT_BUF_INIT;

	cl_git_pass(git_buf_sets(&buf, "/path/to/nonexistent/gitdir"));
	cl_git_pass(git_futils_writebuffer(&buf,
		    fixture.worktree->gitlink, O_RDWR, 0644));

	cl_git_pass(git_worktree_lookup(&wt, fixture.repo, "testrepo-worktree"));
	cl_git_fail(git_repository_open_from_worktree(&repo, wt));

	git_buf_dispose(&buf);
	git_worktree_free(wt);
}