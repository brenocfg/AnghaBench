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
 int /*<<< orphan*/  cfg ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_me ; 
 int /*<<< orphan*/  git_config_get_multivar_foreach (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_snapshot (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 
 int /*<<< orphan*/  snapshot ; 

void test_config_snapshot__multivar(void)
{
	int count;

	count = 0;
	cl_git_mkfile("config", "[old]\nvalue = 5\nvalue = 6\n");
	cl_git_pass(git_config_open_ondisk(&cfg, "config"));
	cl_git_pass(git_config_get_multivar_foreach(cfg, "old.value", NULL, count_me, &count));
	cl_assert_equal_i(2, count);

	count = 0;
	cl_git_pass(git_config_snapshot(&snapshot, cfg));
	cl_git_pass(git_config_get_multivar_foreach(snapshot, "old.value", NULL, count_me, &count));
	cl_assert_equal_i(2, count);

	cl_git_pass(p_unlink("config"));
}