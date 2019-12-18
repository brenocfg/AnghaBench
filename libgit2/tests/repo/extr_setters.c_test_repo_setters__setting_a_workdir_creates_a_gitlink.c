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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ git__prefixcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git__suffixcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (int /*<<< orphan*/ *,char*) ; 
 int git_path_isfile (char*) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_set_workdir (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  repo ; 

void test_repo_setters__setting_a_workdir_creates_a_gitlink(void)
{
	git_config *cfg;
	git_buf buf = GIT_BUF_INIT;
	git_buf content = GIT_BUF_INIT;

	cl_git_pass(git_repository_set_workdir(repo, "./new_workdir", true));

	cl_assert(git_path_isfile("./new_workdir/.git"));

	cl_git_pass(git_futils_readbuffer(&content, "./new_workdir/.git"));
	cl_assert(git__prefixcmp(git_buf_cstr(&content), "gitdir: ") == 0);
	cl_assert(git__suffixcmp(git_buf_cstr(&content), "testrepo.git/") == 0);
	git_buf_dispose(&content);

	cl_git_pass(git_repository_config(&cfg, repo));
	cl_git_pass(git_config_get_string_buf(&buf, cfg, "core.worktree"));
	cl_assert(git__suffixcmp(git_buf_cstr(&buf), "new_workdir/") == 0);

	git_buf_dispose(&buf);
	git_config_free(cfg);
}