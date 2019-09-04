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
 int /*<<< orphan*/  TEST_CONFIG ; 
 int /*<<< orphan*/  assert_config_value (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 

void test_config_stress__trailing_backslash(void)
{
	git_config *config;
	const char *path =  "C:\\iam\\some\\windows\\path\\";

	cl_assert(git_path_exists("git-test-config"));
	cl_git_pass(git_config_open_ondisk(&config, TEST_CONFIG));
	cl_git_pass(git_config_set_string(config, "windows.path", path));
	git_config_free(config);

	cl_git_pass(git_config_open_ondisk(&config, TEST_CONFIG));
	assert_config_value(config, "windows.path", path);

	git_config_free(config);
}