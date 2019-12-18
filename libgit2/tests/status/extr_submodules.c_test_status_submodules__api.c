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

/* Variables and functions */
 scalar_t__ GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (scalar_t__) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_submodule_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_fixture_submodules () ; 

void test_status_submodules__api(void)
{
	git_submodule *sm;

	g_repo = setup_fixture_submodules();

	cl_assert(git_submodule_lookup(NULL, g_repo, "nonexistent") == GIT_ENOTFOUND);

	cl_assert(git_submodule_lookup(NULL, g_repo, "modified") == GIT_ENOTFOUND);

	cl_git_pass(git_submodule_lookup(&sm, g_repo, "testrepo"));
	cl_assert(sm != NULL);
	cl_assert_equal_s("testrepo", git_submodule_name(sm));
	cl_assert_equal_s("testrepo", git_submodule_path(sm));
	git_submodule_free(sm);
}