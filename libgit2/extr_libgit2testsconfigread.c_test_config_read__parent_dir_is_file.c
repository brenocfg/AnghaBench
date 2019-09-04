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
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_SYSTEM ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_cfg_entries_and_compare_levels ; 
 int /*<<< orphan*/  git_config_add_file_ondisk (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_new (int /*<<< orphan*/ **) ; 

void test_config_read__parent_dir_is_file(void)
{
	git_config *cfg;
	int count;

	cl_git_pass(git_config_new(&cfg));
	/*
	 * Verify we can add non-existing files when the parent directory is not
	 * a directory.
	 */
	cl_git_pass(git_config_add_file_ondisk(cfg, "/dev/null/.gitconfig",
		GIT_CONFIG_LEVEL_SYSTEM, NULL, 0));

	count = 0;
	cl_git_pass(git_config_foreach(cfg, count_cfg_entries_and_compare_levels, &count));
	cl_assert_equal_i(0, count);

	git_config_free(cfg);
}