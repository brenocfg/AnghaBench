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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  cfg ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_get_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_snapshot (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 
 int /*<<< orphan*/  snapshot ; 

void test_config_snapshot__create_snapshot(void)
{
	int32_t i;

	cl_git_mkfile("config", "[old]\nvalue = 5\n");
	cl_git_pass(git_config_open_ondisk(&cfg, "config"));
	cl_git_pass(git_config_get_int32(&i, cfg, "old.value"));
	cl_assert_equal_i(5, i);

	cl_git_pass(git_config_snapshot(&snapshot, cfg));

	/* Change the value on the file itself (simulate external process) */
	cl_git_mkfile("config", "[old]\nvalue = 56\n");

	cl_git_pass(git_config_get_int32(&i, cfg, "old.value"));
	cl_assert_equal_i(56, i);
	cl_git_pass(git_config_get_int32(&i, snapshot, "old.value"));
	cl_assert_equal_i(5, i);

	/* Change the value on the file itself (simulate external process) */
	cl_git_mkfile("config", "[old]\nvalue = 999\n");

	/* Old snapshot should still have the old value */
	cl_git_pass(git_config_get_int32(&i, snapshot, "old.value"));
	cl_assert_equal_i(5, i);

	/* New snapshot should see new value */
	git_config_free(snapshot);
	cl_git_pass(git_config_snapshot(&snapshot, cfg));
	cl_git_pass(git_config_get_int32(&i, snapshot, "old.value"));
	cl_assert_equal_i(999, i);

	cl_git_pass(p_unlink("config"));
}