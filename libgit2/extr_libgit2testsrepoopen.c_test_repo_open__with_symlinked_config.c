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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_GLOBAL ; 
 int /*<<< orphan*/  GIT_OPT_SET_SEARCH_PATH ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_sandbox_set_search_path_defaults () ; 
 int /*<<< orphan*/  git_buf_cstr (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_open_default (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_futils_mkdir_r (char*,int) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_prettify (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  symlink (char*,char*) ; 

void test_repo_open__with_symlinked_config(void)
{
#ifndef GIT_WIN32
	git_buf path = GIT_BUF_INIT;
	git_repository *repo;
	git_config *cfg;
	int32_t value;

	cl_git_sandbox_init("empty_standard_repo");

	/* Setup .gitconfig as symlink */
	cl_git_pass(git_futils_mkdir_r("home", 0777));
	cl_git_mkfile("home/.gitconfig.linked", "[global]\ntest = 4567\n");
	cl_must_pass(symlink(".gitconfig.linked", "home/.gitconfig"));
	cl_git_pass(git_path_prettify(&path, "home", NULL));
	cl_git_pass(git_libgit2_opts(GIT_OPT_SET_SEARCH_PATH, GIT_CONFIG_LEVEL_GLOBAL, path.ptr));

	cl_git_pass(git_repository_open(&repo, "empty_standard_repo"));
	cl_git_pass(git_config_open_default(&cfg));
	cl_git_pass(git_config_get_int32(&value, cfg, "global.test"));
	cl_assert_equal_i(4567, value);

	git_config_free(cfg);
	git_repository_free(repo);
	cl_git_pass(git_futils_rmdir_r(git_buf_cstr(&path), NULL, GIT_RMDIR_REMOVE_FILES));
	cl_sandbox_set_search_path_defaults();
	git_buf_dispose(&path);
#endif
}