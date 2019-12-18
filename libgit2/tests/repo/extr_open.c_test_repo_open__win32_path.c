#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; scalar_t__ size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 scalar_t__ git__suffixcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_truncate (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unposix_path (TYPE_1__*) ; 

void test_repo_open__win32_path(void)
{
#ifdef GIT_WIN32
	git_repository *repo = cl_git_sandbox_init("empty_standard_repo"), *repo2;
	git_buf winpath = GIT_BUF_INIT;
	static const char *repo_path = "empty_standard_repo/.git/";
	static const char *repo_wd   = "empty_standard_repo/";

	cl_assert(git__suffixcmp(git_repository_path(repo), repo_path) == 0);
	cl_assert(git__suffixcmp(git_repository_workdir(repo), repo_wd) == 0);

	cl_git_pass(git_buf_sets(&winpath, git_repository_path(repo)));
	unposix_path(&winpath);
	cl_git_pass(git_repository_open(&repo2, winpath.ptr));
	cl_assert(git__suffixcmp(git_repository_path(repo2), repo_path) == 0);
	cl_assert(git__suffixcmp(git_repository_workdir(repo2), repo_wd) == 0);
	git_repository_free(repo2);

	cl_git_pass(git_buf_sets(&winpath, git_repository_path(repo)));
	git_buf_truncate(&winpath, winpath.size - 1); /* remove trailing '/' */
	unposix_path(&winpath);
	cl_git_pass(git_repository_open(&repo2, winpath.ptr));
	cl_assert(git__suffixcmp(git_repository_path(repo2), repo_path) == 0);
	cl_assert(git__suffixcmp(git_repository_workdir(repo2), repo_wd) == 0);
	git_repository_free(repo2);

	cl_git_pass(git_buf_sets(&winpath, git_repository_workdir(repo)));
	unposix_path(&winpath);
	cl_git_pass(git_repository_open(&repo2, winpath.ptr));
	cl_assert(git__suffixcmp(git_repository_path(repo2), repo_path) == 0);
	cl_assert(git__suffixcmp(git_repository_workdir(repo2), repo_wd) == 0);
	git_repository_free(repo2);

	cl_git_pass(git_buf_sets(&winpath, git_repository_workdir(repo)));
	git_buf_truncate(&winpath, winpath.size - 1); /* remove trailing '/' */
	unposix_path(&winpath);
	cl_git_pass(git_repository_open(&repo2, winpath.ptr));
	cl_assert(git__suffixcmp(git_repository_path(repo2), repo_path) == 0);
	cl_assert(git__suffixcmp(git_repository_workdir(repo2), repo_wd) == 0);
	git_repository_free(repo2);

	git_buf_dispose(&winpath);
#endif
}