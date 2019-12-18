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

/* Variables and functions */
 scalar_t__ GIT_SUBMODULE_IGNORE_NONE ; 
 scalar_t__ GIT_SUBMODULE_UPDATE_CHECKOUT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ g_repo ; 
 scalar_t__ git__suffixcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_oid_streq (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_submodule_head_id (int /*<<< orphan*/ *) ; 
 scalar_t__ git_submodule_ignore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_submodule_index_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_lookup (int /*<<< orphan*/ **,scalar_t__,char*) ; 
 int /*<<< orphan*/  git_submodule_name (int /*<<< orphan*/ *) ; 
 scalar_t__ git_submodule_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_path (int /*<<< orphan*/ *) ; 
 scalar_t__ git_submodule_update_strategy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_url (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_submodule_wd_id (int /*<<< orphan*/ *) ; 

void test_submodule_lookup__accessors(void)
{
	git_submodule *sm;
	const char *oid = "480095882d281ed676fe5b863569520e54a7d5c0";

	cl_git_pass(git_submodule_lookup(&sm, g_repo, "sm_unchanged"));
	cl_assert(git_submodule_owner(sm) == g_repo);
	cl_assert_equal_s("sm_unchanged", git_submodule_name(sm));
	cl_assert(git__suffixcmp(git_submodule_path(sm), "sm_unchanged") == 0);
	cl_assert(git__suffixcmp(git_submodule_url(sm), "/submod2_target") == 0);

	cl_assert(git_oid_streq(git_submodule_index_id(sm), oid) == 0);
	cl_assert(git_oid_streq(git_submodule_head_id(sm), oid) == 0);
	cl_assert(git_oid_streq(git_submodule_wd_id(sm), oid) == 0);

	cl_assert(git_submodule_ignore(sm) == GIT_SUBMODULE_IGNORE_NONE);
	cl_assert(git_submodule_update_strategy(sm) == GIT_SUBMODULE_UPDATE_CHECKOUT);

	git_submodule_free(sm);


	cl_git_pass(git_submodule_lookup(&sm, g_repo, "sm_changed_head"));
	cl_assert_equal_s("sm_changed_head", git_submodule_name(sm));

	cl_assert(git_oid_streq(git_submodule_index_id(sm), oid) == 0);
	cl_assert(git_oid_streq(git_submodule_head_id(sm), oid) == 0);
	cl_assert(git_oid_streq(git_submodule_wd_id(sm),
		"3d9386c507f6b093471a3e324085657a3c2b4247") == 0);

	git_submodule_free(sm);


	cl_git_pass(git_submodule_lookup(&sm, g_repo, "sm_added_and_uncommited"));
	cl_assert_equal_s("sm_added_and_uncommited", git_submodule_name(sm));

	cl_assert(git_oid_streq(git_submodule_index_id(sm), oid) == 0);
	cl_assert(git_submodule_head_id(sm) == NULL);
	cl_assert(git_oid_streq(git_submodule_wd_id(sm), oid) == 0);

	git_submodule_free(sm);


	cl_git_pass(git_submodule_lookup(&sm, g_repo, "sm_missing_commits"));
	cl_assert_equal_s("sm_missing_commits", git_submodule_name(sm));

	cl_assert(git_oid_streq(git_submodule_index_id(sm), oid) == 0);
	cl_assert(git_oid_streq(git_submodule_head_id(sm), oid) == 0);
	cl_assert(git_oid_streq(git_submodule_wd_id(sm),
		"5e4963595a9774b90524d35a807169049de8ccad") == 0);

	git_submodule_free(sm);
}