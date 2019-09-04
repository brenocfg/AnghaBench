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
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar__skip () ; 
 int /*<<< orphan*/  do_symlink (char*,char*,int) ; 
 int /*<<< orphan*/  p_lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  should_run () ; 
 int /*<<< orphan*/  strlen (char*) ; 

void test_core_link__lstat_dangling_symlink_directory(void)
{
	struct stat st;

	if (!should_run())
		clar__skip();

	do_symlink("lstat_nonexistent", "lstat_dangling_dir", 1);

	cl_must_fail(p_lstat("lstat_nonexistent", &st));

	cl_must_pass(p_lstat("lstat_dangling_dir", &st));
	cl_assert(S_ISLNK(st.st_mode));
	cl_assert_equal_i(strlen("lstat_nonexistent"), st.st_size);
}