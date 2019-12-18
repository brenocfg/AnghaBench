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
struct TYPE_4__ {int /*<<< orphan*/  count; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_strarray ;

/* Variables and functions */
 int /*<<< orphan*/  _remote_name ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  assert_config_entry_existence (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_rename (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 

void test_network_remote_rename__renaming_a_remote_moves_related_configuration_section(void)
{
	git_strarray problems = {0};

	assert_config_entry_existence(_repo, "remote.test.fetch", true);
	assert_config_entry_existence(_repo, "remote.just/renamed.fetch", false);

	cl_git_pass(git_remote_rename(&problems, _repo, _remote_name, "just/renamed"));
	cl_assert_equal_i(0, problems.count);
	git_strarray_free(&problems);

	assert_config_entry_existence(_repo, "remote.test.fetch", false);
	assert_config_entry_existence(_repo, "remote.just/renamed.fetch", true);
}