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
 int /*<<< orphan*/  GIT_DIR_MODE ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  chdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_repository (char*) ; 
 int /*<<< orphan*/  git__suffixcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_futils_mkdir_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_prettify_dir (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 

void test_repo_init__bare_repo_escaping_current_workdir(void)
{
	git_buf path_repository = GIT_BUF_INIT;
	git_buf path_current_workdir = GIT_BUF_INIT;

	cl_git_pass(git_path_prettify_dir(&path_current_workdir, ".", NULL));

	cl_git_pass(git_buf_joinpath(&path_repository, git_buf_cstr(&path_current_workdir), "a/b/c"));
	cl_git_pass(git_futils_mkdir_r(git_buf_cstr(&path_repository), GIT_DIR_MODE));

	/* Change the current working directory */
	cl_git_pass(chdir(git_buf_cstr(&path_repository)));

	/* Initialize a bare repo with a relative path escaping out of the current working directory */
	cl_git_pass(git_repository_init(&_repo, "../d/e.git", 1));
	cl_git_pass(git__suffixcmp(git_repository_path(_repo), "/a/b/d/e.git/"));

	git_repository_free(_repo);

	/* Open a bare repo with a relative path escaping out of the current working directory */
	cl_git_pass(git_repository_open(&_repo, "../d/e.git"));

	cl_git_pass(chdir(git_buf_cstr(&path_current_workdir)));

	git_buf_dispose(&path_current_workdir);
	git_buf_dispose(&path_repository);

	cleanup_repository("a");
}