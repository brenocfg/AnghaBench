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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_message (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_unlink (int /*<<< orphan*/ ) ; 

void test_repo_message__message(void)
{
	git_buf path = GIT_BUF_INIT, actual = GIT_BUF_INIT;
	const char expected[] = "Test\n\nThis is a test of the emergency broadcast system\n";

	cl_git_pass(git_buf_joinpath(&path, git_repository_path(_repo), "MERGE_MSG"));
	cl_git_mkfile(git_buf_cstr(&path), expected);

	cl_git_pass(git_repository_message(&actual, _repo));
	cl_assert_equal_s(expected, git_buf_cstr(&actual));
	git_buf_dispose(&actual);

	cl_git_pass(p_unlink(git_buf_cstr(&path)));
	cl_assert_equal_i(GIT_ENOTFOUND, git_repository_message(&actual, _repo));
	git_buf_dispose(&path);
}