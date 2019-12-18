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
 int /*<<< orphan*/  assert_submodule_exists (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 
 int /*<<< orphan*/  git_submodule_add_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_add_setup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  git_submodule_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_submodule_add__submodule_clone_into_nonempty_dir_succeeds(void)
{
	git_submodule *sm;

	g_repo = cl_git_sandbox_init("empty_standard_repo");

	cl_git_pass(p_mkdir("empty_standard_repo/sm", 0777));
	cl_git_mkfile("empty_standard_repo/sm/foobar", "");

	/* Create the submodule structure, clone into it and finalize */
	cl_git_pass(git_submodule_add_setup(&sm, g_repo, cl_fixture("testrepo.git"), "sm", true));
	cl_git_pass(git_submodule_clone(NULL, sm, NULL));
	cl_git_pass(git_submodule_add_finalize(sm));

	cl_assert(git_path_exists("empty_standard_repo/sm/foobar"));

	assert_submodule_exists(g_repo, "sm");

	git_submodule_free(sm);
}