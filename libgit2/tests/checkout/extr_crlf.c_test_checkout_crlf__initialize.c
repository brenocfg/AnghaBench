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
 scalar_t__ GIT_EOL_CRLF ; 
 scalar_t__ GIT_EOL_NATIVE ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_path_direach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* systype ; 
 int /*<<< orphan*/  unlink_file ; 

void test_checkout_crlf__initialize(void)
{
	git_buf reponame = GIT_BUF_INIT;

	g_repo = cl_git_sandbox_init("crlf");

	/*
	 * remove the contents of the working directory so that we can
	 * check out over it.
	 */
	cl_git_pass(git_buf_puts(&reponame, "crlf"));
	cl_git_pass(git_path_direach(&reponame, 0, unlink_file, NULL));

	if (GIT_EOL_NATIVE == GIT_EOL_CRLF)
		systype = "windows";
	else
		systype = "posix";

	git_buf_dispose(&reponame);
}