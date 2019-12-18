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
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_GLOBAL ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_LOCAL ; 
 int /*<<< orphan*/  GIT_EEXISTS ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_fail (int) ; 
 int /*<<< orphan*/  cl_git_pass (int) ; 
 int git_config_add_file_ondisk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_new (int /*<<< orphan*/ **) ; 

void test_config_configlevel__adding_the_same_level_twice_returns_EEXISTS(void)
{
	int error;
	git_config *cfg;

	cl_git_pass(git_config_new(&cfg));
	cl_git_pass(git_config_add_file_ondisk(cfg, cl_fixture("config/config9"),
		GIT_CONFIG_LEVEL_LOCAL, NULL, 0));
	cl_git_pass(git_config_add_file_ondisk(cfg, cl_fixture("config/config15"),
		GIT_CONFIG_LEVEL_GLOBAL, NULL, 0));
	error = git_config_add_file_ondisk(cfg, cl_fixture("config/config16"),
		GIT_CONFIG_LEVEL_GLOBAL, NULL, 0);

	cl_git_fail(error);
	cl_assert_equal_i(GIT_EEXISTS, error);

	git_config_free(cfg);
}