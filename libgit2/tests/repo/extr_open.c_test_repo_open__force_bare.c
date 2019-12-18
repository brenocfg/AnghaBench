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
 int GIT_REPOSITORY_OPEN_BARE ; 
 int GIT_REPOSITORY_OPEN_CROSS_FS ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int git_repository_is_bare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_repository_open_bare (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_repository_open_ext (int /*<<< orphan*/ **,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_gitlink_dir (char*,char*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_repo_open__force_bare(void)
{
	/* need to have both repo dir and workdir set up correctly */
	git_repository *repo = cl_git_sandbox_init("empty_standard_repo");
	git_repository *barerepo;

	make_gitlink_dir("alternate", "gitdir: ../empty_standard_repo/.git");

	cl_assert(!git_repository_is_bare(repo));

	cl_git_pass(git_repository_open(&barerepo, "alternate"));
	cl_assert(!git_repository_is_bare(barerepo));
	git_repository_free(barerepo);

	cl_git_pass(git_repository_open_bare(
		&barerepo, "empty_standard_repo/.git"));
	cl_assert(git_repository_is_bare(barerepo));
	git_repository_free(barerepo);

	cl_git_fail(git_repository_open_bare(&barerepo, "alternate/.git"));

	cl_git_pass(git_repository_open_ext(
		&barerepo, "alternate/.git", GIT_REPOSITORY_OPEN_BARE, NULL));
	cl_assert(git_repository_is_bare(barerepo));
	git_repository_free(barerepo);

	cl_git_pass(p_mkdir("empty_standard_repo/subdir", 0777));
	cl_git_mkfile("empty_standard_repo/subdir/something.txt", "something");

	cl_git_fail(git_repository_open_bare(
		&barerepo, "empty_standard_repo/subdir"));

	cl_git_pass(git_repository_open_ext(
		&barerepo, "empty_standard_repo/subdir", GIT_REPOSITORY_OPEN_BARE, NULL));
	cl_assert(git_repository_is_bare(barerepo));
	git_repository_free(barerepo);

	cl_git_pass(p_mkdir("alternate/subdir", 0777));
	cl_git_pass(p_mkdir("alternate/subdir/sub2", 0777));
	cl_git_mkfile("alternate/subdir/sub2/something.txt", "something");

	cl_git_fail(git_repository_open_bare(&barerepo, "alternate/subdir/sub2"));

	cl_git_pass(git_repository_open_ext(
		&barerepo, "alternate/subdir/sub2",
		GIT_REPOSITORY_OPEN_BARE|GIT_REPOSITORY_OPEN_CROSS_FS, NULL));
	cl_assert(git_repository_is_bare(barerepo));
	git_repository_free(barerepo);
}