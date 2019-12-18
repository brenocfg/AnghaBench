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
 int git_path_root (char*) ; 

void test_core_path__12_offset_to_path_root(void)
{
	cl_assert(git_path_root("non/rooted/path") == -1);
	cl_assert(git_path_root("/rooted/path") == 0);

#ifdef GIT_WIN32
	/* Windows specific tests */
	cl_assert(git_path_root("C:non/rooted/path") == -1);
	cl_assert(git_path_root("C:/rooted/path") == 2);
	cl_assert(git_path_root("//computername/sharefolder/resource") == 14);
	cl_assert(git_path_root("//computername/sharefolder") == 14);
	cl_assert(git_path_root("//computername") == -1);
#endif
}