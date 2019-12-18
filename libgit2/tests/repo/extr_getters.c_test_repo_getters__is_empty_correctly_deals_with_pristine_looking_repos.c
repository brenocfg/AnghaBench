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
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_remove_placeholders (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_repository_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ *) ; 

void test_repo_getters__is_empty_correctly_deals_with_pristine_looking_repos(void)
{
	git_repository *repo;

	repo = cl_git_sandbox_init("empty_bare.git");
	cl_git_remove_placeholders(git_repository_path(repo), "dummy-marker.txt");

	cl_assert_equal_i(true, git_repository_is_empty(repo));

	cl_git_sandbox_cleanup();
}