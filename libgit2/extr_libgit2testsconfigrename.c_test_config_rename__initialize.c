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
 int /*<<< orphan*/  g_config ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_config_rename__initialize(void)
{
    g_repo = cl_git_sandbox_init("testrepo.git");
	cl_git_pass(git_repository_config(&g_config, g_repo));
}