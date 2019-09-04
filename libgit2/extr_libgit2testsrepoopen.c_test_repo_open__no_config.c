#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_GLOBAL ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_SYSTEM ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_XDG ; 
 int /*<<< orphan*/  GIT_OPT_SET_SEARCH_PATH ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_fixture_sandbox (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_rename (char*,char*) ; 
 int /*<<< orphan*/  cl_sandbox_set_search_path_defaults () ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_prettify (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_repo_open__no_config(void)
{
	git_buf path = GIT_BUF_INIT;
	git_repository *repo;
	git_config *config;

	cl_fixture_sandbox("empty_standard_repo");
	cl_git_pass(cl_rename(
		"empty_standard_repo/.gitted", "empty_standard_repo/.git"));

	/* remove local config */
	cl_git_pass(git_futils_rmdir_r(
		"empty_standard_repo/.git/config", NULL, GIT_RMDIR_REMOVE_FILES));

	/* isolate from system level configs */
	cl_must_pass(p_mkdir("alternate", 0777));
	cl_git_pass(git_path_prettify(&path, "alternate", NULL));
	cl_git_pass(git_libgit2_opts(
		GIT_OPT_SET_SEARCH_PATH, GIT_CONFIG_LEVEL_GLOBAL, path.ptr));
	cl_git_pass(git_libgit2_opts(
		GIT_OPT_SET_SEARCH_PATH, GIT_CONFIG_LEVEL_SYSTEM, path.ptr));
	cl_git_pass(git_libgit2_opts(
		GIT_OPT_SET_SEARCH_PATH, GIT_CONFIG_LEVEL_XDG, path.ptr));

	git_buf_dispose(&path);

	cl_git_pass(git_repository_open(&repo, "empty_standard_repo"));
	cl_git_pass(git_repository_config(&config, repo));

	cl_git_pass(git_config_set_string(config, "test.set", "42"));

	git_config_free(config);
	git_repository_free(repo);
	cl_fixture_cleanup("empty_standard_repo");

	cl_sandbox_set_search_path_defaults();
}