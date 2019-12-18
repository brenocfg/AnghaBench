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
 int /*<<< orphan*/  GIT_BRANCH_REMOTE ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_branch_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_branch_name (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ref ; 
 int /*<<< orphan*/  repo ; 

void test_refs_branches_name__can_get_remote_branch_name(void)
{
	const char *name;

	cl_git_pass(git_branch_lookup(&ref,repo,"test/master",GIT_BRANCH_REMOTE));
	cl_git_pass(git_branch_name(&name,ref));
	cl_assert_equal_s("test/master",name);
}