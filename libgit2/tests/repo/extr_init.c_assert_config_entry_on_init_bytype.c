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
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_repository ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_get_bool (int*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static void assert_config_entry_on_init_bytype(
	const char *config_key, int expected_value, bool is_bare)
{
	git_config *config;
	int error, current_value;
	const char *repo_path = is_bare ?
		"config_entry/test.bare.git" : "config_entry/test.non.bare.git";

	cl_set_cleanup(&cleanup_repository, "config_entry");

	cl_git_pass(git_repository_init(&_repo, repo_path, is_bare));

	cl_git_pass(git_repository_config(&config, _repo));
	error = git_config_get_bool(&current_value, config, config_key);
	git_config_free(config);

	if (expected_value >= 0) {
		cl_assert_equal_i(0, error);
		cl_assert_equal_i(expected_value, current_value);
	} else {
		cl_assert_equal_i(expected_value, error);
	}
}