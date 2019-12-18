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
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_must_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar__skip () ; 
 int /*<<< orphan*/  do_symlink (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_stat (char*,struct stat*) ; 
 int /*<<< orphan*/  should_run () ; 

void test_core_link__stat_dangling_symlink(void)
{
	struct stat st;

	if (!should_run())
		clar__skip();

	do_symlink("stat_nonexistent", "stat_dangling", 0);

	cl_must_fail(p_stat("stat_nonexistent", &st));
	cl_must_fail(p_stat("stat_dangling", &st));
}