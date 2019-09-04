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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar__skip () ; 
 int /*<<< orphan*/  do_symlink (char*,char*,int) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_stat (char*,struct stat*) ; 
 int /*<<< orphan*/  should_run () ; 

void test_core_link__stat_symlink_directory(void)
{
	struct stat st;

	if (!should_run())
		clar__skip();

	p_mkdir("stat_dirtarget", 0777);
	do_symlink("stat_dirtarget", "stat_dirlink", 1);

	cl_must_pass(p_stat("stat_dirtarget", &st));
	cl_assert(S_ISDIR(st.st_mode));

	cl_must_pass(p_stat("stat_dirlink", &st));
	cl_assert(S_ISDIR(st.st_mode));
}