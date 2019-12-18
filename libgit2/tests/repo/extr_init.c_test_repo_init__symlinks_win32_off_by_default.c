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
 int /*<<< orphan*/  assert_config_entry_on_init (char*,int) ; 
 int /*<<< orphan*/  cl_skip () ; 

void test_repo_init__symlinks_win32_off_by_default(void)
{
#ifndef GIT_WIN32
	cl_skip();
#else
	assert_config_entry_on_init("core.symlinks", false);
#endif
}