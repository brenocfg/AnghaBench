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
 int /*<<< orphan*/  assert_default_branch (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo_a ; 
 int /*<<< orphan*/  git_repository_detach_head (int /*<<< orphan*/ ) ; 

void test_network_remote_defaultbranch__master_on_detached(void)
{
	cl_git_pass(git_repository_detach_head(g_repo_a));
	assert_default_branch("refs/heads/master");
}