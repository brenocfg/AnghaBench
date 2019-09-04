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
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ count_config_entries_match (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_remote_delete (int /*<<< orphan*/ ,char*) ; 

void test_network_remote_delete__remove_remote_configuration_settings(void)
{
	cl_assert(count_config_entries_match(_repo, "remote\\.test\\.+") > 0);

	cl_git_pass(git_remote_delete(_repo, "test"));

	cl_assert_equal_i(0, count_config_entries_match(_repo, "remote\\.test\\.+"));
}