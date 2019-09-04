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
 int GIT_EUNBORNBRANCH ; 
 int /*<<< orphan*/  NON_EXISTING_HEAD ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head_unborn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_head_unborn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  tree ; 

void test_repo_headtree__when_head_is_unborn_returns_EUNBORNBRANCH(void)
{
	make_head_unborn(repo, NON_EXISTING_HEAD);

	cl_assert_equal_i(true, git_repository_head_unborn(repo));

	cl_assert_equal_i(GIT_EUNBORNBRANCH, git_repository_head_tree(&tree, repo));
}