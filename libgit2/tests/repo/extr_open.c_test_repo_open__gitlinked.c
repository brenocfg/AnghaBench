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
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_ (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 scalar_t__ git__suffixcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/ * git_repository_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_gitlink_dir (char*,char*) ; 

void test_repo_open__gitlinked(void)
{
	/* need to have both repo dir and workdir set up correctly */
	git_repository *repo = cl_git_sandbox_init("empty_standard_repo");
	git_repository *repo2;

	make_gitlink_dir("alternate", "gitdir: ../empty_standard_repo/.git");

	cl_git_pass(git_repository_open(&repo2, "alternate"));

	cl_assert(git_repository_path(repo2) != NULL);
	cl_assert_(git__suffixcmp(git_repository_path(repo2), "empty_standard_repo/.git/") == 0, git_repository_path(repo2));
	cl_assert_equal_s(git_repository_path(repo), git_repository_path(repo2));

	cl_assert(git_repository_workdir(repo2) != NULL);
	cl_assert_(git__suffixcmp(git_repository_workdir(repo2), "alternate/") == 0, git_repository_workdir(repo2));

	git_repository_free(repo2);
}