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
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  cl_fixture_sandbox (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cleanup_fixture_submodules ; 
 int /*<<< orphan*/  git_repository_reinit_filesystem (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_rename (char*,char*) ; 
 int /*<<< orphan*/  rewrite_gitmodules (int /*<<< orphan*/ ) ; 

git_repository *setup_fixture_submodules(void)
{
	git_repository *repo = cl_git_sandbox_init("submodules");

	cl_fixture_sandbox("testrepo.git");

	rewrite_gitmodules(git_repository_workdir(repo));
	p_rename("submodules/testrepo/.gitted", "submodules/testrepo/.git");

	cl_set_cleanup(cleanup_fixture_submodules, "testrepo.git");

	cl_git_pass(git_repository_reinit_filesystem(repo, 1));

	return repo;
}