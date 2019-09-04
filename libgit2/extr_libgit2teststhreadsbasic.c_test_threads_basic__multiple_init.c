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
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_libgit2_init () ; 
 int /*<<< orphan*/  git_libgit2_shutdown () ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_threads_basic__multiple_init(void)
{
	git_repository *nested_repo;

	git_libgit2_init();
	cl_git_pass(git_repository_open(&nested_repo, cl_fixture("testrepo.git")));
	git_repository_free(nested_repo);

	git_libgit2_shutdown();
	cl_git_pass(git_repository_open(&nested_repo, cl_fixture("testrepo.git")));
	git_repository_free(nested_repo);
}