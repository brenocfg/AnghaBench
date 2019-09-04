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
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_remote ; 
 int /*<<< orphan*/  g_repo_a ; 
 int /*<<< orphan*/  g_repo_b ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 

void test_network_remote_defaultbranch__initialize(void)
{
	g_repo_a = cl_git_sandbox_init("testrepo.git");
	cl_git_pass(git_repository_init(&g_repo_b, "repo-b.git", true));
	cl_git_pass(git_remote_create(&g_remote, g_repo_b, "origin", git_repository_path(g_repo_a)));
}