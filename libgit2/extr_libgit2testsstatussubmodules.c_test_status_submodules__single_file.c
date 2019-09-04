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
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_status_file (unsigned int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setup_fixture_submodules () ; 

void test_status_submodules__single_file(void)
{
	unsigned int status = 0;
	g_repo = setup_fixture_submodules();
	cl_git_pass( git_status_file(&status, g_repo, "testrepo") );
	cl_assert(!status);
}