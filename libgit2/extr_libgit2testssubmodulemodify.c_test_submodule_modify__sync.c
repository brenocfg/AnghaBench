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
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  assert_submodule_url_is_synced (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string (char const**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_submodule_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_submodule_url (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sync_one_submodule ; 

void test_submodule_modify__sync(void)
{
	git_submodule *sm1, *sm2, *sm3;
	git_config *cfg;
	const char *str;

#define SM1 "sm_unchanged"
#define SM2 "sm_changed_head"
#define SM3 "sm_added_and_uncommited"

	/* look up some submodules */
	cl_git_pass(git_submodule_lookup(&sm1, g_repo, SM1));
	cl_git_pass(git_submodule_lookup(&sm2, g_repo, SM2));
	cl_git_pass(git_submodule_lookup(&sm3, g_repo, SM3));

	/* At this point, the .git/config URLs for the submodules have
	 * not be rewritten with the absolute paths (although the
	 * .gitmodules have.  Let's confirm that they DO NOT match
	 * yet, then we can do a sync to make them match...
	 */

	/* check submodule info does not match before sync */
	cl_git_pass(git_repository_config_snapshot(&cfg, g_repo));
	cl_git_pass(git_config_get_string(&str, cfg, "submodule."SM1".url"));
	cl_assert(strcmp(git_submodule_url(sm1), str) != 0);
	cl_git_pass(git_config_get_string(&str, cfg, "submodule."SM2".url"));
	cl_assert(strcmp(git_submodule_url(sm2), str) != 0);
	cl_git_pass(git_config_get_string(&str, cfg, "submodule."SM3".url"));
	cl_assert(strcmp(git_submodule_url(sm3), str) != 0);
	git_config_free(cfg);

	/* sync all the submodules */
	cl_git_pass(git_submodule_foreach(g_repo, sync_one_submodule, NULL));

	/* check that submodule config is updated */
	assert_submodule_url_is_synced(
		sm1, "submodule."SM1".url", "remote.origin.url");
	assert_submodule_url_is_synced(
		sm2, "submodule."SM2".url", "remote.origin.url");
	assert_submodule_url_is_synced(
		sm3, "submodule."SM3".url", "remote.origin.url");

	git_submodule_free(sm1);
	git_submodule_free(sm2);
	git_submodule_free(sm3);
}