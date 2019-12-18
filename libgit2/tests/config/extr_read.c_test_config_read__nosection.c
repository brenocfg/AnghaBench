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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_nosection_cb ; 

void test_config_read__nosection(void)
{
	git_config *cfg;
	git_buf buf = GIT_BUF_INIT;
	int seen = 0;

	cl_git_pass(git_config_open_ondisk(&cfg, cl_fixture("config/config-nosection")));

	/*
	 * Given a key with no section, we do not allow reading it,
	 * but we do include it in an iteration over the config
	 * store. This appears to match how git's own APIs (and
	 * git-config(1)) behave.
	 */

	cl_git_fail_with(git_config_get_string_buf(&buf, cfg, "key"), GIT_EINVALIDSPEC);

	cl_git_pass(git_config_foreach(cfg, read_nosection_cb, &seen));
	cl_assert_equal_i(seen, 1);

	git_buf_dispose(&buf);
	git_config_free(cfg);
}