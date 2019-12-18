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
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar__skip () ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_rmdir (char*) ; 

void test_repo_init__unwriteable_directory(void)
{
#ifndef GIT_WIN32
	git_repository *repo;

	if (geteuid() == 0)
		clar__skip();

	/*
	 * Create a non-writeable directory so that we cannot create directories
	 * inside of it. The root user has CAP_DAC_OVERRIDE, so he doesn't care
	 * for the directory permissions and thus we need to skip the test if
	 * run as root user.
	 */
	cl_must_pass(p_mkdir("unwriteable", 0444));
	cl_git_fail(git_repository_init(&repo, "unwriteable/repo", 0));
	cl_must_pass(p_rmdir("unwriteable"));
#else
	clar__skip();
#endif
}