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
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_sandbox_set_search_path_defaults () ; 
 int /*<<< orphan*/  git_libgit2_init () ; 
 int /*<<< orphan*/  git_libgit2_shutdown () ; 

void test_core_init__reinit_succeeds(void)
{
	cl_assert_equal_i(0, git_libgit2_shutdown());
	cl_assert_equal_i(1, git_libgit2_init());
	cl_sandbox_set_search_path_defaults();
}