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
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int git_repository_is_bare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_set_workdir (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * git_repository_workdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 

void test_repo_setters__setting_a_workdir_turns_a_bare_repository_into_a_standard_one(void)
{
	cl_assert(git_repository_is_bare(repo) == 1);

	cl_assert(git_repository_workdir(repo) == NULL);
	cl_git_pass(git_repository_set_workdir(repo, "./new_workdir", false));

	cl_assert(git_repository_workdir(repo) != NULL);
	cl_assert(git_repository_is_bare(repo) == 0);
}