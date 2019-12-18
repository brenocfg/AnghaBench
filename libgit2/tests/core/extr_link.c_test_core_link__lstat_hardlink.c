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
 int /*<<< orphan*/  clar__skip () ; 
 int /*<<< orphan*/  do_hardlink (char*,char*) ; 
 int /*<<< orphan*/  p_lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  should_run () ; 

void test_core_link__lstat_hardlink(void)
{
	struct stat st;

	if (!should_run())
		clar__skip();

	cl_git_rewritefile("lstat_hardlink1", "This file has many names!\n");
	do_hardlink("lstat_hardlink1", "lstat_hardlink2");

	cl_must_pass(p_lstat("lstat_hardlink1", &st));
	cl_assert(S_ISREG(st.st_mode));
	cl_assert_equal_i(26, st.st_size);

	cl_must_pass(p_lstat("lstat_hardlink2", &st));
	cl_assert(S_ISREG(st.st_mode));
	cl_assert_equal_i(26, st.st_size);
}