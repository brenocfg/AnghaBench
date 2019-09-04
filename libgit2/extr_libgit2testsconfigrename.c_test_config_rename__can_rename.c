#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ git_config_entry ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_config ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_config_entry_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_get_entry (TYPE_1__**,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_config_rename_section (int /*<<< orphan*/ ,char*,char*) ; 

void test_config_rename__can_rename(void)
{
	git_config_entry *ce;

	cl_git_pass(git_config_get_entry(
		&ce, g_config, "branch.track-local.remote"));
	cl_assert_equal_s(".", ce->value);
	git_config_entry_free(ce);

	cl_git_fail(git_config_get_entry(
		&ce, g_config, "branch.local-track.remote"));

	cl_git_pass(git_config_rename_section(
		g_repo, "branch.track-local", "branch.local-track"));

	cl_git_pass(git_config_get_entry(
		&ce, g_config, "branch.local-track.remote"));
	cl_assert_equal_s(".", ce->value);
	git_config_entry_free(ce);

	cl_git_fail(git_config_get_entry(
		&ce, g_config, "branch.track-local.remote"));
}