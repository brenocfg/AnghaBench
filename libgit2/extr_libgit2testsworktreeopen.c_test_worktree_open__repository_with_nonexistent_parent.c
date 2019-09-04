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
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 char* WORKTREE_REPO ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_fixture_sandbox (char*) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_rename (char*,char*) ; 
 int /*<<< orphan*/  cleanup_fixture_worktree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fixture ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  p_chdir (char*) ; 

void test_worktree_open__repository_with_nonexistent_parent(void)
{
	git_repository *repo;

	cleanup_fixture_worktree(&fixture);

	cl_fixture_sandbox(WORKTREE_REPO);
	cl_git_pass(p_chdir(WORKTREE_REPO));
	cl_git_pass(cl_rename(".gitted", ".git"));
	cl_git_pass(p_chdir(".."));

	cl_git_fail(git_repository_open(&repo, WORKTREE_REPO));

	cl_fixture_cleanup(WORKTREE_REPO);
}