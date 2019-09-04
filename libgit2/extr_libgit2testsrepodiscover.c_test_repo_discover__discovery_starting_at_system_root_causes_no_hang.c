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

void test_repo_discover__discovery_starting_at_system_root_causes_no_hang(void)
{
#ifdef GIT_WIN32
	git_buf out = GIT_BUF_INIT;
	cl_git_fail(git_repository_discover(&out, "C:/", 0, NULL));
	cl_git_fail(git_repository_discover(&out, "//localhost/", 0, NULL));
#endif
}