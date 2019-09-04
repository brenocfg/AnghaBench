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
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void ensure_workdir_contents(const char *path, const char *contents)
{
	git_buf fullpath = GIT_BUF_INIT, data_buf = GIT_BUF_INIT;

	cl_git_pass(
		git_buf_joinpath(&fullpath, git_repository_workdir(g_repo), path));

	cl_git_pass(git_futils_readbuffer(&data_buf, git_buf_cstr(&fullpath)));
	cl_assert(strcmp(git_buf_cstr(&data_buf), contents) == 0);

	git_buf_dispose(&fullpath);
	git_buf_dispose(&data_buf);
}