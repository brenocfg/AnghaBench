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
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * g_child ; 
 int /*<<< orphan*/ * g_module ; 
 int /*<<< orphan*/ * g_parent ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 

void test_submodule_open__cleanup(void)
{
	git_submodule_free(g_module);
	git_repository_free(g_child);
	cl_git_sandbox_cleanup();
	g_parent = NULL;
	g_child = NULL;
	g_module = NULL;
}