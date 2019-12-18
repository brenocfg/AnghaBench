#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_clone_options ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CLONE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_remote_url (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_style_unc_path (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  unc_path (TYPE_1__*,char*,char const*) ; 

void test_clone_local__standard_unc_paths_are_written_git_style(void)
{
#ifdef GIT_WIN32
	git_repository *repo;
	git_remote *remote;
	git_clone_options opts = GIT_CLONE_OPTIONS_INIT;
	git_buf unc = GIT_BUF_INIT, git_unc = GIT_BUF_INIT;

	/* we use a fixture path because it needs to exist for us to want to clone */
	const char *path = cl_fixture("testrepo.git");

	cl_git_pass(unc_path(&unc, "localhost", path));
	cl_git_pass(git_style_unc_path(&git_unc, "localhost", path));

	cl_git_pass(git_clone(&repo, unc.ptr, "./clone.git", &opts));
	cl_git_pass(git_remote_lookup(&remote, repo, "origin"));

	cl_assert_equal_s(git_unc.ptr, git_remote_url(remote));

	git_remote_free(remote);
	git_repository_free(repo);
	git_buf_dispose(&unc);
	git_buf_dispose(&git_unc);

	cl_git_pass(git_futils_rmdir_r("./clone.git", NULL, GIT_RMDIR_REMOVE_FILES));
#endif
}