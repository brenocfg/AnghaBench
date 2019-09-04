#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct update_submodule_cb_payload {int checkout_progress_called; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {struct update_submodule_cb_payload* progress_payload; int /*<<< orphan*/  progress_cb; } ;
struct TYPE_9__ {TYPE_1__ checkout_opts; } ;
typedef  TYPE_2__ git_submodule_update_options ;
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_10__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_3__ git_checkout_options ;

/* Variables and functions */
 TYPE_3__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_SUBMODULE_IGNORE_UNSPECIFIED ; 
 int GIT_SUBMODULE_STATUS_IN_CONFIG ; 
 int GIT_SUBMODULE_STATUS_IN_HEAD ; 
 int GIT_SUBMODULE_STATUS_IN_INDEX ; 
 int GIT_SUBMODULE_STATUS_IN_WD ; 
 int GIT_SUBMODULE_STATUS_WD_MODIFIED ; 
 int GIT_SUBMODULE_STATUS_WD_UNINITIALIZED ; 
 TYPE_2__ GIT_SUBMODULE_UPDATE_OPTIONS_INIT ; 
 int /*<<< orphan*/  checkout_progress_cb ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_oid_streq (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_set_head (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_head_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_index_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_submodule_status (unsigned int*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_submodule_update (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  git_submodule_wd_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_fixture_submodule_simple () ; 

void test_submodule_update__update_already_checked_out_submodule(void)
{
	git_submodule *sm = NULL;
	git_checkout_options checkout_options = GIT_CHECKOUT_OPTIONS_INIT;
	git_submodule_update_options update_options = GIT_SUBMODULE_UPDATE_OPTIONS_INIT;
	unsigned int submodule_status = 0;
	git_reference *branch_reference = NULL;
	git_object *branch_commit = NULL;
	struct update_submodule_cb_payload update_payload = { 0 };

	g_repo = setup_fixture_submodule_simple();

	update_options.checkout_opts.progress_cb = checkout_progress_cb;
	update_options.checkout_opts.progress_payload = &update_payload;

	/* Initialize and update the sub repository */
	cl_git_pass(git_submodule_lookup(&sm, g_repo, "testrepo"));

	cl_git_pass(git_submodule_status(&submodule_status, g_repo, "testrepo", GIT_SUBMODULE_IGNORE_UNSPECIFIED));
	cl_assert_equal_i(submodule_status, GIT_SUBMODULE_STATUS_IN_HEAD |
		GIT_SUBMODULE_STATUS_IN_INDEX |
		GIT_SUBMODULE_STATUS_IN_CONFIG |
		GIT_SUBMODULE_STATUS_WD_UNINITIALIZED);

	cl_git_pass(git_submodule_update(sm, 1, &update_options));

	/* verify expected state */
	cl_assert(git_oid_streq(git_submodule_head_id(sm), "be3563ae3f795b2b4353bcce3a527ad0a4f7f644") == 0);
	cl_assert(git_oid_streq(git_submodule_wd_id(sm), "be3563ae3f795b2b4353bcce3a527ad0a4f7f644") == 0);
	cl_assert(git_oid_streq(git_submodule_index_id(sm), "be3563ae3f795b2b4353bcce3a527ad0a4f7f644") == 0);

	/* checkout the alternate_1 branch */
	checkout_options.checkout_strategy = GIT_CHECKOUT_SAFE;

	cl_git_pass(git_reference_lookup(&branch_reference, g_repo, "refs/heads/alternate_1"));
	cl_git_pass(git_reference_peel(&branch_commit, branch_reference, GIT_OBJECT_COMMIT));
	cl_git_pass(git_checkout_tree(g_repo, branch_commit, &checkout_options));
	cl_git_pass(git_repository_set_head(g_repo, git_reference_name(branch_reference)));

	/*
	 * Verify state after checkout of parent repository. The submodule ID in the
	 * HEAD commit and index should be updated, but not the workdir.
	 */

	cl_git_pass(git_submodule_status(&submodule_status, g_repo, "testrepo", GIT_SUBMODULE_IGNORE_UNSPECIFIED));

	git_submodule_free(sm);
	cl_git_pass(git_submodule_lookup(&sm, g_repo, "testrepo"));

	cl_assert_equal_i(submodule_status, GIT_SUBMODULE_STATUS_IN_HEAD |
		GIT_SUBMODULE_STATUS_IN_INDEX |
		GIT_SUBMODULE_STATUS_IN_CONFIG |
		GIT_SUBMODULE_STATUS_IN_WD |
		GIT_SUBMODULE_STATUS_WD_MODIFIED);

	cl_assert(git_oid_streq(git_submodule_head_id(sm), "a65fedf39aefe402d3bb6e24df4d4f5fe4547750") == 0);
	cl_assert(git_oid_streq(git_submodule_wd_id(sm), "be3563ae3f795b2b4353bcce3a527ad0a4f7f644") == 0);
	cl_assert(git_oid_streq(git_submodule_index_id(sm), "a65fedf39aefe402d3bb6e24df4d4f5fe4547750") == 0);

	/*
	 * Update the submodule and verify the state.
	 * Now, the HEAD, index, and Workdir commits should all be updated to
	 * the new commit.
	 */
	cl_git_pass(git_submodule_update(sm, 0, &update_options));
	cl_assert(git_oid_streq(git_submodule_head_id(sm), "a65fedf39aefe402d3bb6e24df4d4f5fe4547750") == 0);
	cl_assert(git_oid_streq(git_submodule_wd_id(sm), "a65fedf39aefe402d3bb6e24df4d4f5fe4547750") == 0);
	cl_assert(git_oid_streq(git_submodule_index_id(sm), "a65fedf39aefe402d3bb6e24df4d4f5fe4547750") == 0);

	/* verify that the expected callbacks have been called. */
	cl_assert_equal_i(1, update_payload.checkout_progress_called);

	git_submodule_free(sm);
	git_object_free(branch_commit);
	git_reference_free(branch_reference);
}