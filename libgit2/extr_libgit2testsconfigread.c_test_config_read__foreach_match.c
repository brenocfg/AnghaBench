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
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_cfg_entries ; 
 int /*<<< orphan*/  git_config_foreach_match (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_config_read__foreach_match(void)
{
	git_config *cfg;
	int count;

	cl_git_pass(git_config_open_ondisk(&cfg, cl_fixture("config/config9")));

	count = 0;
	cl_git_pass(
		git_config_foreach_match(cfg, "core.*", count_cfg_entries, &count));
	cl_assert_equal_i(3, count);

	count = 0;
	cl_git_pass(
		git_config_foreach_match(cfg, "remote\\.ab.*", count_cfg_entries, &count));
	cl_assert_equal_i(2, count);

	count = 0;
	cl_git_pass(
		git_config_foreach_match(cfg, ".*url$", count_cfg_entries, &count));
	cl_assert_equal_i(2, count);

	count = 0;
	cl_git_pass(
		git_config_foreach_match(cfg, ".*dummy.*", count_cfg_entries, &count));
	cl_assert_equal_i(2, count);

	count = 0;
	cl_git_pass(
		git_config_foreach_match(cfg, ".*nomatch.*", count_cfg_entries, &count));
	cl_assert_equal_i(0, count);

	git_config_free(cfg);
}