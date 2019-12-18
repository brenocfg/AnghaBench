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
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  assert_config_entry_value (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_path_isdir (char*) ; 
 int /*<<< orphan*/  git_path_isfile (char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_submodule_repo_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setup_fixture_submod2 () ; 

void test_submodule_repository_init__basic(void)
{
	git_submodule *sm;
	git_repository *repo;
	git_buf dot_git_content = GIT_BUF_INIT;

	g_repo = setup_fixture_submod2();

	cl_git_pass(git_submodule_lookup(&sm, g_repo, "sm_gitmodules_only"));
	cl_git_pass(git_submodule_init(sm, 0));
	cl_git_pass(git_submodule_repo_init(&repo, sm, 1));

	/* Verify worktree */
	assert_config_entry_value(repo, "core.worktree", "../../../sm_gitmodules_only/");

	/* Verify gitlink */
	cl_git_pass(git_futils_readbuffer(&dot_git_content, "submod2/" "sm_gitmodules_only" "/.git"));
	cl_assert_equal_s("gitdir: ../.git/modules/sm_gitmodules_only/", dot_git_content.ptr);

	cl_assert(git_path_isfile("submod2/" "sm_gitmodules_only" "/.git"));

	cl_assert(git_path_isdir("submod2/.git/modules"));
	cl_assert(git_path_isdir("submod2/.git/modules/" "sm_gitmodules_only"));
	cl_assert(git_path_isfile("submod2/.git/modules/" "sm_gitmodules_only" "/HEAD"));

	git_submodule_free(sm);
	git_repository_free(repo);
	git_buf_dispose(&dot_git_content);
}