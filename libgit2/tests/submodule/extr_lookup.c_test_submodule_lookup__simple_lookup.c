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

/* Variables and functions */
 int /*<<< orphan*/  GIT_EEXISTS ; 
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  assert_submodule_exists (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  refute_submodule_exists (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void test_submodule_lookup__simple_lookup(void)
{
	assert_submodule_exists(g_repo, "sm_unchanged");

	/* lookup pending change in .gitmodules that is not in HEAD */
	assert_submodule_exists(g_repo, "sm_added_and_uncommited");

	/* lookup pending change in .gitmodules that is not in HEAD nor index */
	assert_submodule_exists(g_repo, "sm_gitmodules_only");

	/* lookup git repo subdir that is not added as submodule */
	refute_submodule_exists(g_repo, "not-submodule", GIT_EEXISTS);

	/* lookup existing directory that is not a submodule */
	refute_submodule_exists(g_repo, "just_a_dir", GIT_ENOTFOUND);

	/* lookup existing file that is not a submodule */
	refute_submodule_exists(g_repo, "just_a_file", GIT_ENOTFOUND);

	/* lookup non-existent item */
	refute_submodule_exists(g_repo, "no_such_file", GIT_ENOTFOUND);

	/* lookup a submodule by path with a trailing slash */
	assert_submodule_exists(g_repo, "sm_added_and_uncommited/");
}