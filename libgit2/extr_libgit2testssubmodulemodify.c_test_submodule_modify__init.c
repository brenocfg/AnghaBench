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
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_one_config ; 
 int /*<<< orphan*/  g_repo ; 
 scalar_t__ git__suffixcmp (char const*,char*) ; 
 int /*<<< orphan*/  git_config_foreach_match (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string (char const**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_submodule_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_one_submodule ; 

void test_submodule_modify__init(void)
{
	git_config *cfg;
	const char *str;

	/* erase submodule data from .git/config */
	cl_git_pass(git_repository_config(&cfg, g_repo));
	cl_git_pass(
		git_config_foreach_match(cfg, "submodule\\..*", delete_one_config, cfg));
	git_config_free(cfg);

	/* confirm no submodule data in config */
	cl_git_pass(git_repository_config_snapshot(&cfg, g_repo));
	cl_git_fail_with(GIT_ENOTFOUND, git_config_get_string(&str, cfg, "submodule.sm_unchanged.url"));
	cl_git_fail_with(GIT_ENOTFOUND, git_config_get_string(&str, cfg, "submodule.sm_changed_head.url"));
	cl_git_fail_with(GIT_ENOTFOUND, git_config_get_string(&str, cfg, "submodule.sm_added_and_uncommited.url"));
	git_config_free(cfg);

	/* call init and see that settings are copied */
	cl_git_pass(git_submodule_foreach(g_repo, init_one_submodule, NULL));

	/* confirm submodule data in config */
	cl_git_pass(git_repository_config_snapshot(&cfg, g_repo));
	cl_git_pass(git_config_get_string(&str, cfg, "submodule.sm_unchanged.url"));
	cl_assert(git__suffixcmp(str, "/submod2_target") == 0);
	cl_git_pass(git_config_get_string(&str, cfg, "submodule.sm_changed_head.url"));
	cl_assert(git__suffixcmp(str, "/submod2_target") == 0);
	cl_git_pass(git_config_get_string(&str, cfg, "submodule.sm_added_and_uncommited.url"));
	cl_assert(git__suffixcmp(str, "/submod2_target") == 0);
	git_config_free(cfg);
}