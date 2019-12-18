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
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  foreach_cb ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_submodule_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_submodule_lookup__duplicated_path(void)
{
	cl_git_rewritefile("submod2/.gitmodules",
			   "[submodule \"sm1\"]\n"
			   "    path = duplicated-path\n"
			   "    url = sm1\n"
			   "[submodule \"sm2\"]\n"
			   "    path = duplicated-path\n"
			   "    url = sm2\n");

	cl_git_fail(git_submodule_foreach(g_repo, foreach_cb, NULL));
}