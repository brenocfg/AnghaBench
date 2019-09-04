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
typedef  int /*<<< orphan*/  git_reflog ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_REFLOG_DIR ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_join_n (int /*<<< orphan*/ *,char,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int git_path_isfile (int /*<<< orphan*/ ) ; 
 scalar_t__ git_reflog_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 

void test_refs_reflog_reflog__reading_the_reflog_from_a_reference_with_no_log_returns_an_empty_one(void)
{
	git_reflog *reflog;
	const char *refname = "refs/heads/subtrees";
	git_buf subtrees_log_path = GIT_BUF_INIT;

	git_buf_join_n(&subtrees_log_path, '/', 3, git_repository_path(g_repo), GIT_REFLOG_DIR, refname);
	cl_assert_equal_i(false, git_path_isfile(git_buf_cstr(&subtrees_log_path)));

	cl_git_pass(git_reflog_read(&reflog, g_repo, refname));

	cl_assert_equal_i(0, (int)git_reflog_entrycount(reflog));

	git_reflog_free(reflog);
	git_buf_dispose(&subtrees_log_path);
}