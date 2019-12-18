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
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_repository_open_ext (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_repo_open__check_if_repository(void)
{
	cl_git_sandbox_init("empty_standard_repo");

	/* Pass NULL for the output parameter to check for but not open the repo */
	cl_git_pass(git_repository_open_ext(NULL, "empty_standard_repo", 0, NULL));
	cl_git_fail(git_repository_open_ext(NULL, "repo_does_not_exist", 0, NULL));

	cl_fixture_cleanup("empty_standard_repo");
}