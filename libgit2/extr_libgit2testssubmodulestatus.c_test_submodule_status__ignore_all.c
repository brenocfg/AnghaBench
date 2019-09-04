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
typedef  int /*<<< orphan*/  git_submodule_ignore_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EEXISTS ; 
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_SUBMODULE_IGNORE_ALL ; 
 int /*<<< orphan*/  GIT_SUBMODULE_STATUS_IS_UNMODIFIED (unsigned int) ; 
 int /*<<< orphan*/  add_submodule_to_index (char*) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_futils_mkdir_relative (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_status (unsigned int*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refute_submodule_exists (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rm_submodule (char*) ; 

void test_submodule_status__ignore_all(void)
{
	unsigned int status;
	git_submodule_ignore_t ign = GIT_SUBMODULE_IGNORE_ALL;

	rm_submodule("sm_unchanged");

	refute_submodule_exists(g_repo, "just_a_dir", GIT_ENOTFOUND);
	refute_submodule_exists(g_repo, "not-submodule", GIT_EEXISTS);
	refute_submodule_exists(g_repo, "not", GIT_EEXISTS);

	cl_git_pass(git_submodule_status(&status, g_repo,"sm_changed_index", ign));
	cl_assert(GIT_SUBMODULE_STATUS_IS_UNMODIFIED(status));

	cl_git_pass(git_submodule_status(&status, g_repo,"sm_changed_head", ign));
	cl_assert(GIT_SUBMODULE_STATUS_IS_UNMODIFIED(status));

	cl_git_pass(git_submodule_status(&status, g_repo,"sm_changed_file", ign));
	cl_assert(GIT_SUBMODULE_STATUS_IS_UNMODIFIED(status));

	cl_git_pass(git_submodule_status(&status, g_repo,"sm_changed_untracked_file", ign));
	cl_assert(GIT_SUBMODULE_STATUS_IS_UNMODIFIED(status));

	cl_git_pass(git_submodule_status(&status, g_repo,"sm_missing_commits", ign));
	cl_assert(GIT_SUBMODULE_STATUS_IS_UNMODIFIED(status));

	cl_git_pass(git_submodule_status(&status, g_repo,"sm_added_and_uncommited", ign));
	cl_assert(GIT_SUBMODULE_STATUS_IS_UNMODIFIED(status));

	/* removed sm_unchanged for deleted workdir */
	cl_git_pass(git_submodule_status(&status, g_repo,"sm_unchanged", ign));
	cl_assert(GIT_SUBMODULE_STATUS_IS_UNMODIFIED(status));

	/* now mkdir sm_unchanged to test uninitialized */
	cl_git_pass(git_futils_mkdir_relative("sm_unchanged", "submod2", 0755, 0, NULL));
	cl_git_pass(git_submodule_status(&status, g_repo,"sm_unchanged", ign));
	cl_assert(GIT_SUBMODULE_STATUS_IS_UNMODIFIED(status));

	/* update sm_changed_head in index */
	add_submodule_to_index("sm_changed_head");
	cl_git_pass(git_submodule_status(&status, g_repo,"sm_changed_head", ign));
	cl_assert(GIT_SUBMODULE_STATUS_IS_UNMODIFIED(status));
}