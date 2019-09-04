#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_7__ {int /*<<< orphan*/  checkout_options; } ;
typedef  TYPE_1__ git_rebase_options ;
typedef  int /*<<< orphan*/  git_rebase_operation ;
typedef  int /*<<< orphan*/  git_rebase ;
struct TYPE_8__ {int* progress_payload; int /*<<< orphan*/  progress_cb; } ;
typedef  TYPE_2__ git_checkout_options ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 TYPE_2__ GIT_CHECKOUT_OPTIONS_INIT ; 
 TYPE_1__ GIT_REBASE_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_annotated_commit_from_ref (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rebase_abort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rebase_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rebase_init (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_rebase_next (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  rebase_checkout_progress_cb ; 
 int /*<<< orphan*/  repo ; 

void test_rebase_merge__custom_checkout_options(void)
{
	git_rebase *rebase;
	git_reference *branch_ref, *upstream_ref;
	git_annotated_commit *branch_head, *upstream_head;
	git_rebase_options rebase_options = GIT_REBASE_OPTIONS_INIT;
	git_checkout_options checkout_options = GIT_CHECKOUT_OPTIONS_INIT;
	git_rebase_operation *rebase_operation;
	int called = 0;

	checkout_options.progress_cb = rebase_checkout_progress_cb;
	checkout_options.progress_payload = &called;

	memcpy(&rebase_options.checkout_options, &checkout_options,
		sizeof(git_checkout_options));

	cl_git_pass(git_reference_lookup(&branch_ref, repo, "refs/heads/beef"));
	cl_git_pass(git_reference_lookup(&upstream_ref, repo, "refs/heads/master"));

	cl_git_pass(git_annotated_commit_from_ref(&branch_head, repo, branch_ref));
	cl_git_pass(git_annotated_commit_from_ref(&upstream_head, repo, upstream_ref));

	called = 0;
	cl_git_pass(git_rebase_init(&rebase, repo, branch_head, upstream_head, NULL, &rebase_options));
	cl_assert_equal_i(1, called);

	called = 0;
	cl_git_pass(git_rebase_next(&rebase_operation, rebase));
	cl_assert_equal_i(1, called);

	called = 0;
	cl_git_pass(git_rebase_abort(rebase));
	cl_assert_equal_i(1, called);

	git_annotated_commit_free(branch_head);
	git_annotated_commit_free(upstream_head);
	git_reference_free(branch_ref);
	git_reference_free(upstream_ref);
	git_rebase_free(rebase);
}