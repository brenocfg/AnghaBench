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
 int /*<<< orphan*/  do_symlink (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_stat (char*,struct stat*) ; 
 int /*<<< orphan*/  should_run () ; 

void test_core_link__stat_symlink(void)
{
	struct stat st;

	if (!should_run())
		clar__skip();

	cl_git_rewritefile("stat_target", "This is the target of a symbolic link.\n");
	do_symlink("stat_target", "stat_symlink", 0);

	cl_must_pass(p_stat("stat_target", &st));
	cl_assert(S_ISREG(st.st_mode));
	cl_assert_equal_i(39, st.st_size);

	cl_must_pass(p_stat("stat_symlink", &st));
	cl_assert(S_ISREG(st.st_mode));
	cl_assert_equal_i(39, st.st_size);
}