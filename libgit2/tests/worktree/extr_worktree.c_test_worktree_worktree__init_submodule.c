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
typedef  int /*<<< orphan*/  git_worktree ;
struct TYPE_12__ {int /*<<< orphan*/  gitdir; int /*<<< orphan*/  commondir; int /*<<< orphan*/  workdir; } ;
typedef  TYPE_1__ git_repository ;
struct TYPE_13__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_fixture_worktree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fixture ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_path_prettify_dir (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_open (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_open_from_worktree (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_worktree_add (int /*<<< orphan*/ **,TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_worktree_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* setup_fixture_submod2 () ; 

void test_worktree_worktree__init_submodule(void)
{
	git_repository *repo, *sm, *wt;
	git_worktree *worktree;
	git_buf path = GIT_BUF_INIT;

	cleanup_fixture_worktree(&fixture);
	repo = setup_fixture_submod2();

	cl_git_pass(git_buf_joinpath(&path, repo->workdir, "sm_unchanged"));
	cl_git_pass(git_repository_open(&sm, path.ptr));
	cl_git_pass(git_buf_joinpath(&path, repo->workdir, "../worktree/"));
	cl_git_pass(git_worktree_add(&worktree, sm, "repo-worktree", path.ptr, NULL));
	cl_git_pass(git_repository_open_from_worktree(&wt, worktree));

	cl_git_pass(git_path_prettify_dir(&path, path.ptr, NULL));
	cl_assert_equal_s(path.ptr, wt->workdir);
	cl_git_pass(git_path_prettify_dir(&path, sm->commondir, NULL));
	cl_assert_equal_s(sm->commondir, wt->commondir);

	cl_git_pass(git_buf_joinpath(&path, sm->gitdir, "worktrees/repo-worktree/"));
	cl_assert_equal_s(path.ptr, wt->gitdir);

	git_buf_dispose(&path);
	git_worktree_free(worktree);
	git_repository_free(sm);
	git_repository_free(wt);
}