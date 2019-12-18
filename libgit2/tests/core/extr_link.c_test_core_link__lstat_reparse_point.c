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
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_custom_reparse (char*) ; 
 int /*<<< orphan*/  p_lstat (char*,struct stat*) ; 

void test_core_link__lstat_reparse_point(void)
{
#ifdef GIT_WIN32
	struct stat st;

	cl_git_rewritefile("lstat_reparse", "This is a reparse point!\n");
	do_custom_reparse("lstat_reparse");

	cl_must_pass(p_lstat("lstat_reparse", &st));
	cl_assert(S_ISREG(st.st_mode));
	cl_assert_equal_i(25, st.st_size);
#endif
}