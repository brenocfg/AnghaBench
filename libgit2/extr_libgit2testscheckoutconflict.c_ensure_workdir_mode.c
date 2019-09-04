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
struct stat {int st_mode; } ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int S_IRWXU ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static void ensure_workdir_mode(const char *path, int mode)
{
#ifdef GIT_WIN32
	GIT_UNUSED(path);
	GIT_UNUSED(mode);
#else
	git_buf fullpath = GIT_BUF_INIT;
	struct stat st;

	cl_git_pass(
		git_buf_joinpath(&fullpath, git_repository_workdir(g_repo), path));

	cl_git_pass(p_stat(git_buf_cstr(&fullpath), &st));
	cl_assert_equal_i((mode & S_IRWXU), (st.st_mode & S_IRWXU));

	git_buf_dispose(&fullpath);
#endif
}