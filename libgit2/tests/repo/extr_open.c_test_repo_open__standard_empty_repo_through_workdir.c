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
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 scalar_t__ git__suffixcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * git_repository_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_repository_workdir (int /*<<< orphan*/ *) ; 

void test_repo_open__standard_empty_repo_through_workdir(void)
{
	git_repository *repo = cl_git_sandbox_init("empty_standard_repo");

	cl_assert(git_repository_path(repo) != NULL);
	cl_assert(git__suffixcmp(git_repository_path(repo), "/") == 0);

	cl_assert(git_repository_workdir(repo) != NULL);
	cl_assert(git__suffixcmp(git_repository_workdir(repo), "/") == 0);
}