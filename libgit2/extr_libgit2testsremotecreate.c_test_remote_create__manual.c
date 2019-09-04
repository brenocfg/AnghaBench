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
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 char* TEST_URL ; 
 int /*<<< orphan*/  _config ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_remote_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_url (int /*<<< orphan*/ *) ; 

void test_remote_create__manual(void)
{
	git_remote *remote;
	cl_git_pass(git_config_set_string(_config, "remote.origin.fetch", "+refs/heads/*:refs/remotes/origin/*"));
	cl_git_pass(git_config_set_string(_config, "remote.origin.url", TEST_URL));

	cl_git_pass(git_remote_lookup(&remote, _repo, "origin"));
	cl_assert_equal_s(git_remote_name(remote), "origin");
	cl_assert_equal_s(git_remote_url(remote), TEST_URL);

	git_remote_free(remote);
}