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
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_GLOBAL ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_LOCAL ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_SYSTEM ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_add_file_ondisk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_new (int /*<<< orphan*/ **) ; 

void test_config_read__fallback_from_local_to_global_and_from_global_to_system(void)
{
	git_config *cfg;
	int32_t i;

	cl_git_pass(git_config_new(&cfg));
	cl_git_pass(git_config_add_file_ondisk(cfg, cl_fixture("config/config9"),
		GIT_CONFIG_LEVEL_SYSTEM, NULL, 0));
	cl_git_pass(git_config_add_file_ondisk(cfg, cl_fixture("config/config15"),
		GIT_CONFIG_LEVEL_GLOBAL, NULL, 0));
	cl_git_pass(git_config_add_file_ondisk(cfg, cl_fixture("config/config16"),
		GIT_CONFIG_LEVEL_LOCAL, NULL, 0));

	cl_git_pass(git_config_get_int32(&i, cfg, "core.global"));
	cl_assert_equal_i(17, i);
	cl_git_pass(git_config_get_int32(&i, cfg, "core.system"));
	cl_assert_equal_i(11, i);

	git_config_free(cfg);
}