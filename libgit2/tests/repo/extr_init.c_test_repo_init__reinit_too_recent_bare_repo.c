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
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_set_int32 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ *,char*,int) ; 

void test_repo_init__reinit_too_recent_bare_repo(void)
{
	git_config *config;

	/* Initialize the repository */
	cl_git_pass(git_repository_init(&_repo, "reinit.git", 1));
	git_repository_config(&config, _repo);

	/*
	 * Hack the config of the repository to make it look like it has
	 * been created by a recenter version of git/libgit2
	 */
	cl_git_pass(git_config_set_int32(config, "core.repositoryformatversion", 42));

	git_config_free(config);
	git_repository_free(_repo);

	/* Try to reinitialize the repository */
	cl_git_fail(git_repository_init(&_repo, "reinit.git", 1));

	cl_fixture_cleanup("reinit.git");
}