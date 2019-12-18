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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_GLOBAL ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_LOCAL ; 
 scalar_t__ GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (scalar_t__) ; 
 scalar_t__ git_config_add_file_ondisk (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_config_delete_entry (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_config_get_int32 (int*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ git_config_new (int /*<<< orphan*/ **) ; 
 scalar_t__ git_config_open_level (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 
 scalar_t__ git_config_set_int32 (int /*<<< orphan*/ *,char*,int) ; 

void test_config_write__delete_value_at_specific_level(void)
{
	git_config *cfg, *cfg_specific;
	int32_t i;

	cl_git_pass(git_config_open_ondisk(&cfg, "config15"));
	cl_git_pass(git_config_get_int32(&i, cfg, "core.dummy2"));
	cl_assert(i == 7);
	git_config_free(cfg);

	cl_git_pass(git_config_new(&cfg));
	cl_git_pass(git_config_add_file_ondisk(cfg, "config9",
		GIT_CONFIG_LEVEL_LOCAL, NULL, 0));
	cl_git_pass(git_config_add_file_ondisk(cfg, "config15",
		GIT_CONFIG_LEVEL_GLOBAL, NULL, 0));

	cl_git_pass(git_config_open_level(&cfg_specific, cfg, GIT_CONFIG_LEVEL_GLOBAL));

	cl_git_pass(git_config_delete_entry(cfg_specific, "core.dummy2"));
	git_config_free(cfg);

	cl_git_pass(git_config_open_ondisk(&cfg, "config15"));
	cl_assert(git_config_get_int32(&i, cfg, "core.dummy2") == GIT_ENOTFOUND);
	cl_git_pass(git_config_set_int32(cfg, "core.dummy2", 7));

	git_config_free(cfg_specific);
	git_config_free(cfg);
}