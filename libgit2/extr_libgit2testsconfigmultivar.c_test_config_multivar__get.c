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
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_APP ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_GLOBAL ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_LOCAL ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_SYSTEM ; 
 int /*<<< orphan*/  check_get_multivar (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  check_get_multivar_foreach (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_add_file_ondisk (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 

void test_config_multivar__get(void)
{
	git_config *cfg;

	cl_git_pass(git_config_open_ondisk(&cfg, "config/config11"));
	check_get_multivar_foreach(cfg, 2, 1);

	/* add another that has the _name entry */
	cl_git_pass(git_config_add_file_ondisk(cfg, "config/config9", GIT_CONFIG_LEVEL_SYSTEM, NULL, 1));
	check_get_multivar_foreach(cfg, 3, 2);

	/* add another that does not have the _name entry */
	cl_git_pass(git_config_add_file_ondisk(cfg, "config/config0", GIT_CONFIG_LEVEL_GLOBAL, NULL, 1));
	check_get_multivar_foreach(cfg, 3, 2);

	/* add another that does not have the _name entry at the end */
	cl_git_pass(git_config_add_file_ondisk(cfg, "config/config1", GIT_CONFIG_LEVEL_APP, NULL, 1));
	check_get_multivar_foreach(cfg, 3, 2);

	/* drop original file */
	cl_git_pass(git_config_add_file_ondisk(cfg, "config/config2", GIT_CONFIG_LEVEL_LOCAL, NULL, 1));
	check_get_multivar_foreach(cfg, 1, 1);

	/* drop other file with match */
	cl_git_pass(git_config_add_file_ondisk(cfg, "config/config3", GIT_CONFIG_LEVEL_SYSTEM, NULL, 1));
	check_get_multivar_foreach(cfg, 0, 0);

	/* reload original file (add different place in order) */
	cl_git_pass(git_config_add_file_ondisk(cfg, "config/config11", GIT_CONFIG_LEVEL_SYSTEM, NULL, 1));
	check_get_multivar_foreach(cfg, 2, 1);

	check_get_multivar(cfg, 2);

	git_config_free(cfg);
}