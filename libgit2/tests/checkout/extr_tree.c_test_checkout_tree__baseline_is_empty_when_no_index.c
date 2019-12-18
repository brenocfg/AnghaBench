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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_4__ {size_t* notify_payload; int /*<<< orphan*/  checkout_strategy; int /*<<< orphan*/  notify_cb; int /*<<< orphan*/  notify_flags; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 int /*<<< orphan*/  GIT_CHECKOUT_NOTIFY_CONFLICT ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_ECONFLICT ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  assert_on_branch (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  assert_status_entrycount (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checkout_conflict_count_cb ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,size_t) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_checkout_tree__baseline_is_empty_when_no_index(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_reference *head;
	git_object *obj;
	size_t conflicts = 0;

	assert_on_branch(g_repo, "master");

	cl_git_pass(git_repository_head(&head, g_repo));
	cl_git_pass(git_reference_peel(&obj, head, GIT_OBJECT_COMMIT));

	cl_git_pass(git_reset(g_repo, obj, GIT_RESET_HARD, NULL));

	cl_must_pass(p_unlink("testrepo/.git/index"));

	/* for a safe checkout, we should have checkout conflicts with
	 * the existing untracked files.
	 */
	opts.checkout_strategy &= ~GIT_CHECKOUT_FORCE;
	opts.notify_flags = GIT_CHECKOUT_NOTIFY_CONFLICT;
	opts.notify_cb = checkout_conflict_count_cb;
	opts.notify_payload = &conflicts;

	cl_git_fail_with(GIT_ECONFLICT, git_checkout_tree(g_repo, obj, &opts));
	cl_assert_equal_i(4, conflicts);

	/* but force should succeed and update the index */
	opts.checkout_strategy |= GIT_CHECKOUT_FORCE;
	cl_git_pass(git_checkout_tree(g_repo, obj, &opts));

	assert_status_entrycount(g_repo, 0);

	git_object_free(obj);
	git_reference_free(head);
}