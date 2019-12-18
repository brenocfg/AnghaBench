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
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  fake_submod_cb ; 
 int /*<<< orphan*/  git_submodule_add_setup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  git_submodule_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 

void test_submodule_nosubs__add(void)
{
	git_repository *repo = cl_git_sandbox_init("status");
	git_submodule *sm, *sm2;

	cl_git_pass(git_submodule_add_setup(&sm, repo, "https://github.com/libgit2/libgit2.git", "submodules/libgit2", 1));

	cl_git_pass(git_submodule_lookup(&sm2, repo, "submodules/libgit2"));
	git_submodule_free(sm2);

	cl_git_pass(git_submodule_foreach(repo, fake_submod_cb, NULL));

	git_submodule_free(sm);
}