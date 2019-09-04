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
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_repository ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ *,char*,int) ; 

void test_repo_init__reinit_bare_repo(void)
{
	cl_set_cleanup(&cleanup_repository, "reinit.git");

	/* Initialize the repository */
	cl_git_pass(git_repository_init(&_repo, "reinit.git", 1));
	git_repository_free(_repo);

	/* Reinitialize the repository */
	cl_git_pass(git_repository_init(&_repo, "reinit.git", 1));
}