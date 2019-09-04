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
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  assert_config_entry_existence (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_delete (int /*<<< orphan*/ ,char*) ; 

void test_network_remote_delete__remove_branch_upstream_configuration_settings(void)
{
	assert_config_entry_existence(_repo, "branch.mergeless.remote", true);
	assert_config_entry_existence(_repo, "branch.master.remote", true);

	cl_git_pass(git_remote_delete(_repo, "test"));

	assert_config_entry_existence(_repo, "branch.mergeless.remote", false);
	assert_config_entry_existence(_repo, "branch.mergeless.merge", false);
	assert_config_entry_existence(_repo, "branch.master.remote", false);
	assert_config_entry_existence(_repo, "branch.master.merge", false);
}