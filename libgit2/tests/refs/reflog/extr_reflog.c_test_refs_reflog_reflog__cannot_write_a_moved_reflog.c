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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_rename (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reflog_write (int /*<<< orphan*/ *) ; 

void test_refs_reflog_reflog__cannot_write_a_moved_reflog(void)
{
	git_reference *master, *new_master;
	git_buf master_log_path = GIT_BUF_INIT, moved_log_path = GIT_BUF_INIT;
	git_reflog *reflog;

	cl_git_pass(git_reference_lookup(&master, g_repo, "refs/heads/master"));
	cl_git_pass(git_reflog_read(&reflog, g_repo, "refs/heads/master"));

	cl_git_pass(git_reflog_write(reflog));

	cl_git_pass(git_reference_rename(&new_master, master, "refs/moved", 0, NULL));
	git_reference_free(master);

	cl_git_fail(git_reflog_write(reflog));

	git_reflog_free(reflog);
	git_reference_free(new_master);
	git_buf_dispose(&moved_log_path);
	git_buf_dispose(&master_log_path);
}