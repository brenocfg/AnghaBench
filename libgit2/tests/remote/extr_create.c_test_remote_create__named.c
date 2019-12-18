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
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 char* TEST_URL ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (size_t,size_t) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 size_t count_config_entries_match (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string (char const**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 char const* git_remote_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_owner (int /*<<< orphan*/ *) ; 
 char const* git_remote_url (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_remote_create__named(void)
{
	git_remote *remote;
	git_config *cfg;
	const char *cfg_val;

	size_t section_count = count_config_entries_match(_repo, "remote\\.");

	cl_git_pass(git_remote_create(&remote, _repo, "valid-name", TEST_URL));

	cl_assert_equal_s(git_remote_name(remote), "valid-name");
	cl_assert_equal_s(git_remote_url(remote), TEST_URL);
	cl_assert_equal_p(git_remote_owner(remote), _repo);

	cl_git_pass(git_repository_config_snapshot(&cfg, _repo));

	cl_git_pass(git_config_get_string(&cfg_val, cfg, "remote.valid-name.fetch"));
	cl_assert_equal_s(cfg_val, "+refs/heads/*:refs/remotes/valid-name/*");

	cl_git_pass(git_config_get_string(&cfg_val, cfg, "remote.valid-name.url"));
	cl_assert_equal_s(cfg_val, TEST_URL);

	cl_assert_equal_i(section_count + 2, count_config_entries_match(_repo, "remote\\."));

	git_config_free(cfg);
	git_remote_free(remote);
}