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
struct TYPE_4__ {int /*<<< orphan*/ * strings; int /*<<< orphan*/  count; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  _remote_name ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  assert_config_entry_value (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_remote_rename (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_config__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 

void test_network_remote_rename__renaming_a_remote_notifies_of_non_default_fetchrefspec(void)
{
	git_config *config;
	git_remote *remote;
	git_strarray problems = {0};

	cl_git_pass(git_repository_config__weakptr(&config, _repo));
	cl_git_pass(git_config_set_string(config, "remote.test.fetch", "+refs/*:refs/*"));
	cl_git_pass(git_remote_lookup(&remote, _repo, "test"));
	git_remote_free(remote);

	cl_git_pass(git_remote_rename(&problems, _repo, _remote_name, "just/renamed"));
	cl_assert_equal_i(1, problems.count);
	cl_assert_equal_s("+refs/*:refs/*", problems.strings[0]);
	git_strarray_free(&problems);

	assert_config_entry_value(_repo, "remote.just/renamed.fetch", "+refs/*:refs/*");

	git_strarray_free(&problems);
}