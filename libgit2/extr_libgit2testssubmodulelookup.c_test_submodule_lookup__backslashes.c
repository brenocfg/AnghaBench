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
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_submodule_open (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_resolve_url (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_submodule_url (int /*<<< orphan*/ *) ; 

void test_submodule_lookup__backslashes(void)
{
	git_config *cfg;
	git_submodule *sm;
	git_repository *subrepo;
	git_buf buf = GIT_BUF_INIT;
	const char *backslashed_path = "..\\submod2_target";

	cl_git_pass(git_config_open_ondisk(&cfg, "submod2/.gitmodules"));
	cl_git_pass(git_config_set_string(cfg, "submodule.sm_unchanged.url", backslashed_path));
	git_config_free(cfg);

	cl_git_pass(git_submodule_lookup(&sm, g_repo, "sm_unchanged"));
	cl_assert_equal_s(backslashed_path, git_submodule_url(sm));
	cl_git_pass(git_submodule_open(&subrepo, sm));

	cl_git_pass(git_submodule_resolve_url(&buf, g_repo, backslashed_path));

	git_buf_dispose(&buf);
	git_submodule_free(sm);
	git_repository_free(subrepo);
}