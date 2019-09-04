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

void test_win32_longpath__errmsg_on_checkout(void)
{
#ifdef GIT_WIN32
	git_repository *repo;

	cl_git_fail(git_clone(&repo, cl_fixture("testrepo.git"), path.ptr, NULL));
	assert_name_too_long();
#endif
}