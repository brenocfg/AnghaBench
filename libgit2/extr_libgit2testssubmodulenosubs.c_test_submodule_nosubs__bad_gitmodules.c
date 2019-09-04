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
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_submodule_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

void test_submodule_nosubs__bad_gitmodules(void)
{
	git_repository *repo = cl_git_sandbox_init("status");

	cl_git_mkfile("status/.gitmodules", "[submodule \"foobar\"]\tpath=blargle\n\turl=\n\tbranch=\n\tupdate=flooble\n\n");

	cl_git_rewritefile("status/.gitmodules", "[submodule \"foobar\"]\tpath=blargle\n\turl=\n\tbranch=\n\tupdate=rebase\n\n");

	cl_git_pass(git_submodule_lookup(NULL, repo, "foobar"));
	cl_assert_equal_i(GIT_ENOTFOUND, git_submodule_lookup(NULL, repo, "subdir"));
}