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
 int /*<<< orphan*/  assert_sm_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_child ; 
 int /*<<< orphan*/  g_module ; 
 int /*<<< orphan*/  g_parent ; 
 int /*<<< orphan*/  git_submodule_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_submodule_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_submodule_open__opening_via_lookup_succeeds(void)
{
	cl_git_pass(git_submodule_lookup(&g_module, g_parent, "sm_unchanged"));
	cl_git_pass(git_submodule_open(&g_child, g_module));
	assert_sm_valid(g_parent, g_child, "sm_unchanged");
}