#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* workdir_path; int flags; } ;
typedef  TYPE_1__ git_repository_init_options ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int GIT_REPOSITORY_INIT_MKPATH ; 
 int GIT_REPOSITORY_INIT_NO_DOTGIT_DIR ; 
 TYPE_1__ GIT_REPOSITORY_INIT_OPTIONS_INIT ; 
 int GIT_REPOSITORY_INIT_RELATIVE_GITLINK ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  assert_config_entry_value (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_repository (char*) ; 
 int /*<<< orphan*/  git__suffixcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  git_repository_init_ext (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_is_bare (int /*<<< orphan*/ ) ; 
 int git_repository_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 

void test_repo_init__relative_gitdir(void)
{
	git_repository_init_options opts = GIT_REPOSITORY_INIT_OPTIONS_INIT;
	git_buf dot_git_content = GIT_BUF_INIT;

	opts.workdir_path = "../c_wd";
	opts.flags =
		GIT_REPOSITORY_INIT_MKPATH |
		GIT_REPOSITORY_INIT_RELATIVE_GITLINK |
		GIT_REPOSITORY_INIT_NO_DOTGIT_DIR;

	/* make the directory first, then it should succeed */
	cl_git_pass(git_repository_init_ext(&_repo, "root/b/my_repository", &opts));

	cl_assert(!git__suffixcmp(git_repository_workdir(_repo), "root/b/c_wd/"));
	cl_assert(!git__suffixcmp(git_repository_path(_repo), "root/b/my_repository/"));
	cl_assert(!git_repository_is_bare(_repo));
	cl_assert(git_repository_is_empty(_repo));

	/* Verify that the gitlink and worktree entries are relative */

	/* Verify worktree */
	assert_config_entry_value(_repo, "core.worktree", "../c_wd/");

	/* Verify gitlink */
	cl_git_pass(git_futils_readbuffer(&dot_git_content, "root/b/c_wd/.git"));
	cl_assert_equal_s("gitdir: ../my_repository/", dot_git_content.ptr);

	git_buf_dispose(&dot_git_content);
	cleanup_repository("root");
}