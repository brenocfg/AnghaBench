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
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_is_bare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 

void test_repo_new__has_nothing(void)
{
	git_repository *repo;

	cl_git_pass(git_repository_new(&repo));
	cl_assert_equal_b(true, git_repository_is_bare(repo));
	cl_assert_equal_p(NULL, git_repository_path(repo));
	cl_assert_equal_p(NULL, git_repository_workdir(repo));
	git_repository_free(repo);
}