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
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_submodule_name (int /*<<< orphan*/ *) ; 

void test_submodule_lookup__prefix_name(void)
{
	git_submodule *sm;

	cl_git_rewritefile("submod2/.gitmodules",
			   "[submodule \"Test_App\"]\n"
			   "    path = Test_App\n"
			   "    url = ../Test_App\n"
			   "[submodule \"Test_App2\"]\n"
			   "    path = Test_App2\n"
			   "    url = ../Test_App\n");

	cl_git_pass(git_submodule_lookup(&sm, g_repo, "Test_App"));
	cl_assert_equal_s("Test_App", git_submodule_name(sm));

	git_submodule_free(sm);

	cl_git_pass(git_submodule_lookup(&sm, g_repo, "Test_App2"));
	cl_assert_equal_s("Test_App2", git_submodule_name(sm));

	git_submodule_free(sm);
}