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
 int /*<<< orphan*/  GIT_EEXISTS ; 
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_submodule_nosubs__lookup(void)
{
	git_repository *repo = cl_git_sandbox_init("status");
	git_submodule *sm = NULL;

	p_mkdir("status/subrepo", 0777);
	cl_git_mkfile("status/subrepo/.git", "gitdir: ../.git");

	cl_assert_equal_i(GIT_ENOTFOUND, git_submodule_lookup(&sm, repo, "subdir"));

	cl_assert_equal_i(GIT_EEXISTS, git_submodule_lookup(&sm, repo, "subrepo"));

	cl_assert_equal_i(GIT_ENOTFOUND, git_submodule_lookup(&sm, repo, "subdir"));

	cl_assert_equal_i(GIT_EEXISTS, git_submodule_lookup(&sm, repo, "subrepo"));
}