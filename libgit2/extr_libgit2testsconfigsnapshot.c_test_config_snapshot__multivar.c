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
 int /*<<< orphan*/  cl_git_mkfile (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_me ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_multivar_foreach (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  git_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

void test_config_snapshot__multivar(void)
{
	int count = 0;
	git_config *cfg, *snapshot;
	const char *filename = "config-file";

	cl_git_mkfile(filename, "[old]\nvalue = 5\nvalue = 6\n");

	cl_git_pass(git_config_open_ondisk(&cfg, filename));
	cl_git_pass(git_config_get_multivar_foreach(cfg, "old.value", NULL, count_me, &count));

	cl_assert_equal_i(2, count);

	cl_git_pass(git_config_snapshot(&snapshot, cfg));
	git_config_free(cfg);

	count = 0;
	cl_git_pass(git_config_get_multivar_foreach(snapshot, "old.value", NULL, count_me, &count));

	cl_assert_equal_i(2, count);

	git_config_free(snapshot);
}