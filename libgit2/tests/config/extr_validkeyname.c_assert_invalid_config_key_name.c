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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  cfg ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_delete_entry (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_config_get_multivar_foreach (int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_config_set_multivar (int /*<<< orphan*/ ,char const*,char*,char*) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ ,char const*,char*) ; 

__attribute__((used)) static void assert_invalid_config_key_name(const char *name)
{
	git_buf buf = GIT_BUF_INIT;

	cl_git_fail_with(git_config_get_string_buf(&buf, cfg, name),
		GIT_EINVALIDSPEC);
	cl_git_fail_with(git_config_set_string(cfg, name, "42"),
		GIT_EINVALIDSPEC);
	cl_git_fail_with(git_config_delete_entry(cfg, name),
		GIT_EINVALIDSPEC);
	cl_git_fail_with(git_config_get_multivar_foreach(cfg, name, "*", NULL, NULL),
		GIT_EINVALIDSPEC);
	cl_git_fail_with(git_config_set_multivar(cfg, name, "*", "42"),
		GIT_EINVALIDSPEC);
}