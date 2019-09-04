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

void test_core_link__stat_reparse_point(void)
{
#ifdef GIT_WIN32
	struct stat st;

	/* Generic reparse points should be treated as regular files, only
	 * symlinks and junctions should be treated as links.
	 */

	cl_git_rewritefile("stat_reparse", "This is a reparse point!\n");
	do_custom_reparse("stat_reparse");

	cl_must_pass(p_lstat("stat_reparse", &st));
	cl_assert(S_ISREG(st.st_mode));
	cl_assert_equal_i(25, st.st_size);
#endif
}