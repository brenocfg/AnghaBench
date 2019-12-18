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
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_SYSTEM ; 
 int /*<<< orphan*/  cfg_callback_countdown ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_fail (int) ; 
 int /*<<< orphan*/  cl_git_pass (int) ; 
 int /*<<< orphan*/  count_cfg_entries_and_compare_levels ; 
 int git_config_add_file_ondisk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_config_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_new (int /*<<< orphan*/ **) ; 

void test_config_read__foreach(void)
{
	git_config *cfg;
	int count, ret;

	cl_git_pass(git_config_new(&cfg));
	cl_git_pass(git_config_add_file_ondisk(cfg, cl_fixture("config/config9"),
		GIT_CONFIG_LEVEL_SYSTEM, NULL, 0));
	cl_git_pass(git_config_add_file_ondisk(cfg, cl_fixture("config/config15"),
		GIT_CONFIG_LEVEL_GLOBAL, NULL, 0));

	count = 0;
	cl_git_pass(git_config_foreach(cfg, count_cfg_entries_and_compare_levels, &count));
	cl_assert_equal_i(7, count);

	count = 3;
	cl_git_fail(ret = git_config_foreach(cfg, cfg_callback_countdown, &count));
	cl_assert_equal_i(-100, ret);

	git_config_free(cfg);
}