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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 char* GIT_REFLOG_DIR ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_path_isfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 

void test_refs_reflog_reflog__deleting_the_reference_deletes_the_reflog(void)
{
	git_reference *master;
	git_buf master_log_path = GIT_BUF_INIT;

	git_buf_joinpath(&master_log_path, git_repository_path(g_repo), GIT_REFLOG_DIR);
	git_buf_joinpath(&master_log_path, git_buf_cstr(&master_log_path), "refs/heads/master");

	cl_assert_equal_i(true, git_path_isfile(git_buf_cstr(&master_log_path)));

	cl_git_pass(git_reference_lookup(&master, g_repo, "refs/heads/master"));
	cl_git_pass(git_reference_delete(master));
	git_reference_free(master);

	cl_assert_equal_i(false, git_path_isfile(git_buf_cstr(&master_log_path)));
	git_buf_dispose(&master_log_path);
}