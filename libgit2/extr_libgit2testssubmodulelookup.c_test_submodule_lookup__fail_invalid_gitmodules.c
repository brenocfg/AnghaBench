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
typedef  int /*<<< orphan*/  sm_lookup_data ;
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_submodule_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sm_lookup_cb ; 

void test_submodule_lookup__fail_invalid_gitmodules(void)
{
	git_submodule *sm;
	sm_lookup_data data;
	memset(&data, 0, sizeof(data));

	cl_git_rewritefile("submod2/.gitmodules",
			   "[submodule \"Test_App\"\n"
			   "    path = Test_App\n"
			   "    url = ../Test_App\n");

	cl_git_fail(git_submodule_lookup(&sm, g_repo, "Test_App"));

	cl_git_fail(git_submodule_foreach(g_repo, sm_lookup_cb, &data));
}