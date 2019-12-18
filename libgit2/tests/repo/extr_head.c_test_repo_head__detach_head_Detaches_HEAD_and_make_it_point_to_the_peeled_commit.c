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
 int /*<<< orphan*/  assert_head_is_correctly_detached () ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_detach_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head_detached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 

void test_repo_head__detach_head_Detaches_HEAD_and_make_it_point_to_the_peeled_commit(void)
{
	cl_assert_equal_i(false, git_repository_head_detached(repo));

	cl_git_pass(git_repository_detach_head(repo));

	assert_head_is_correctly_detached();
}