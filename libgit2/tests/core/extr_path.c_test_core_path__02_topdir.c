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
 int /*<<< orphan*/  check_topdir (char*,char*) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_path_topdir (char*) ; 

void test_core_path__02_topdir(void)
{
	check_topdir(".git/", ".git/");
	check_topdir("/.git/", ".git/");
	check_topdir("usr/local/.git/", ".git/");
	check_topdir("./.git/", ".git/");
	check_topdir("/usr/.git/", ".git/");
	check_topdir("/", "/");
	check_topdir("a/", "a/");

	cl_assert(git_path_topdir("/usr/.git") == NULL);
	cl_assert(git_path_topdir(".") == NULL);
	cl_assert(git_path_topdir("") == NULL);
	cl_assert(git_path_topdir("a") == NULL);
}