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

/* Variables and functions */

void test_clone_local__git_style_unc_paths(void)
{
#ifdef GIT_WIN32
	git_repository *repo;
	git_remote *remote;
	git_clone_options opts = GIT_CLONE_OPTIONS_INIT;
	git_buf git_unc = GIT_BUF_INIT;

	/* we use a fixture path because it needs to exist for us to want to clone */
	const char *path = cl_fixture("testrepo.git");

	cl_git_pass(git_style_unc_path(&git_unc, "localhost", path));

	cl_git_pass(git_clone(&repo, git_unc.ptr, "./clone.git", &opts));
	cl_git_pass(git_remote_lookup(&remote, repo, "origin"));

	cl_assert_equal_s(git_unc.ptr, git_remote_url(remote));

	git_remote_free(remote);
	git_repository_free(repo);
	git_buf_dispose(&git_unc);

	cl_git_pass(git_futils_rmdir_r("./clone.git", NULL, GIT_RMDIR_REMOVE_FILES));
#endif
}