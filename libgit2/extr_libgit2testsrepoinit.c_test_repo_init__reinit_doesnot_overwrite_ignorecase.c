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
 int /*<<< orphan*/ * _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_repository ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_int32 (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_set_int32 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int) ; 

void test_repo_init__reinit_doesnot_overwrite_ignorecase(void)
{
	git_config *config;
	int current_value;

	/* Init a new repo */
	cl_set_cleanup(&cleanup_repository, "not.overwrite.git");
	cl_git_pass(git_repository_init(&_repo, "not.overwrite.git", 1));

	/* Change the "core.ignorecase" config value to something unlikely */
	git_repository_config(&config, _repo);
	git_config_set_int32(config, "core.ignorecase", 42);
	git_config_free(config);
	git_repository_free(_repo);
	_repo = NULL;

	/* Reinit the repository */
	cl_git_pass(git_repository_init(&_repo, "not.overwrite.git", 1));
	git_repository_config(&config, _repo);

	/* Ensure the "core.ignorecase" config value hasn't been updated */
	cl_git_pass(git_config_get_int32(&current_value, config, "core.ignorecase"));
	cl_assert_equal_i(42, current_value);

	git_config_free(config);
}