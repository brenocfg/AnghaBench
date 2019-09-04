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
 int /*<<< orphan*/  cl_assert_equal_b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_is_bare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_repository_set_workdir (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_repo_new__is_bare_until_workdir_set(void)
{
	git_repository *repo;

	cl_git_pass(git_repository_new(&repo));
	cl_assert_equal_b(true, git_repository_is_bare(repo));

	cl_git_pass(git_repository_set_workdir(repo, clar_sandbox_path(), 0));
	cl_assert_equal_b(false, git_repository_is_bare(repo));

	git_repository_free(repo);
}