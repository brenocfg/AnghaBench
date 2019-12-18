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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_STATUS_CURRENT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,unsigned int) ; 
 int /*<<< orphan*/  cl_git_mkfile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_remove_placeholders (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_file (unsigned int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  p_rename (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stage_and_commit (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void assert_ignore_case(
	bool should_ignore_case,
	int expected_lower_cased_file_status,
	int expected_camel_cased_file_status)
{
	unsigned int status;
	git_buf lower_case_path = GIT_BUF_INIT, camel_case_path = GIT_BUF_INIT;
	git_repository *repo, *repo2;

	repo = cl_git_sandbox_init("empty_standard_repo");
	cl_git_remove_placeholders(git_repository_path(repo), "dummy-marker.txt");

	cl_repo_set_bool(repo, "core.ignorecase", should_ignore_case);

	cl_git_pass(git_buf_joinpath(&lower_case_path,
		git_repository_workdir(repo), "plop"));

	cl_git_mkfile(git_buf_cstr(&lower_case_path), "");

	stage_and_commit(repo, "plop");

	cl_git_pass(git_repository_open(&repo2, "./empty_standard_repo"));

	cl_git_pass(git_status_file(&status, repo2, "plop"));
	cl_assert_equal_i(GIT_STATUS_CURRENT, status);

	cl_git_pass(git_buf_joinpath(&camel_case_path,
		git_repository_workdir(repo), "Plop"));

	cl_git_pass(p_rename(git_buf_cstr(&lower_case_path), git_buf_cstr(&camel_case_path)));

	cl_git_pass(git_status_file(&status, repo2, "plop"));
	cl_assert_equal_i(expected_lower_cased_file_status, status);

	cl_git_pass(git_status_file(&status, repo2, "Plop"));
	cl_assert_equal_i(expected_camel_cased_file_status, status);

	git_repository_free(repo2);
	git_buf_dispose(&lower_case_path);
	git_buf_dispose(&camel_case_path);
}