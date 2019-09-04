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
 int /*<<< orphan*/  GIT_MKDIR_PATH ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_futils_mkdir (char*,int,int /*<<< orphan*/ ) ; 

void test_core_stat__initialize(void)
{
	cl_git_pass(git_futils_mkdir("root/d1/d2", 0755, GIT_MKDIR_PATH));
	cl_git_mkfile("root/file", "whatever\n");
	cl_git_mkfile("root/d1/file", "whatever\n");
}