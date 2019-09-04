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

git_repository *setup_fixture_submod3(void)
{
	git_repository *repo = cl_git_sandbox_init("submod3");

	cl_fixture_sandbox("submod2_target");
	p_rename("submod2_target/.gitted", "submod2_target/.git");

	rewrite_gitmodules(git_repository_workdir(repo));
	p_rename("submod3/One/.gitted", "submod3/One/.git");
	p_rename("submod3/TWO/.gitted", "submod3/TWO/.git");
	p_rename("submod3/three/.gitted", "submod3/three/.git");
	p_rename("submod3/FoUr/.gitted", "submod3/FoUr/.git");
	p_rename("submod3/Five/.gitted", "submod3/Five/.git");
	p_rename("submod3/six/.gitted", "submod3/six/.git");
	p_rename("submod3/sEvEn/.gitted", "submod3/sEvEn/.git");
	p_rename("submod3/EIGHT/.gitted", "submod3/EIGHT/.git");
	p_rename("submod3/nine/.gitted", "submod3/nine/.git");
	p_rename("submod3/TEN/.gitted", "submod3/TEN/.git");

	cl_set_cleanup(cleanup_fixture_submodules, "submod2_target");

	cl_git_pass(git_repository_reinit_filesystem(repo, 1));

	return repo;
}