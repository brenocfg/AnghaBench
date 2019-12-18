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
 int /*<<< orphan*/  clar__skip () ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 

void test_repo_init__nonexisting_root(void)
{
#ifdef GIT_WIN32
	git_repository *repo;

	/*
	 * This really only depends on the nonexistence of the Q: drive. We
	 * cannot implement the equivalent test on Unix systems, as there is
	 * fundamentally no path that is disconnected from the root directory.
	 */
	cl_git_fail(git_repository_init(&repo, "Q:/non/existent/path", 0));
	cl_git_fail(git_repository_init(&repo, "Q:\\non\\existent\\path", 0));
#else
	clar__skip();
#endif
}