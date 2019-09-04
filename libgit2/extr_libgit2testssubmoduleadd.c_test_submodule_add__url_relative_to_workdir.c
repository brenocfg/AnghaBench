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
 int /*<<< orphan*/  assert_submodule_url (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_submodule_add_setup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 

void test_submodule_add__url_relative_to_workdir(void)
{
	git_submodule *sm;

	/* In this repo, HEAD (master) has no remote tracking branc h*/
	g_repo = cl_git_sandbox_init("testrepo");

	cl_git_pass(
		git_submodule_add_setup(&sm, g_repo, "./", "TestGitRepository", 1)
		);
	git_submodule_free(sm);

	assert_submodule_url("TestGitRepository", git_repository_workdir(g_repo));
}