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
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 

void test_repo_init__nonexistent_paths(void)
{
	git_repository *repo;

#ifdef GIT_WIN32
	cl_git_fail(git_repository_init(&repo, "Q:/non/existent/path", 0));
	cl_git_fail(git_repository_init(&repo, "Q:\\non\\existent\\path", 0));
#else
	cl_git_fail(git_repository_init(&repo, "/non/existent/path", 0));
#endif
}