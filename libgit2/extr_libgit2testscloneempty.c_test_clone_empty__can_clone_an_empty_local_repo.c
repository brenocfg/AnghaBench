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
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_repository ; 
 int /*<<< orphan*/  g_options ; 
 int /*<<< orphan*/  g_repo_cloned ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 

void test_clone_empty__can_clone_an_empty_local_repo(void)
{
	cl_set_cleanup(&cleanup_repository, "./empty");

	cl_git_pass(git_clone(&g_repo_cloned, "./empty_bare.git", "./empty", &g_options));
}