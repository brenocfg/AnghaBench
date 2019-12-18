#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_7__ {int* payload; int /*<<< orphan*/ * transfer_progress; } ;
struct TYPE_8__ {TYPE_2__ callbacks; } ;
struct TYPE_6__ {int* progress_payload; int /*<<< orphan*/ * progress_cb; int /*<<< orphan*/  checkout_strategy; } ;
struct TYPE_9__ {TYPE_3__ fetch_opts; TYPE_1__ checkout_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_SAFE ; 
 int GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  LIVE_REPO_URL ; 
 int /*<<< orphan*/  checkout_progress ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_progress ; 
 TYPE_4__ g_options ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int git_path_isfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_symbolic_target (int /*<<< orphan*/ *) ; 
 int git_reference_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 

void test_online_clone__can_checkout_a_cloned_repo(void)
{
	git_buf path = GIT_BUF_INIT;
	git_reference *head;
	bool checkout_progress_cb_was_called = false,
		  fetch_progress_cb_was_called = false;

	g_options.checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE;
	g_options.checkout_opts.progress_cb = &checkout_progress;
	g_options.checkout_opts.progress_payload = &checkout_progress_cb_was_called;
	g_options.fetch_opts.callbacks.transfer_progress = &fetch_progress;
	g_options.fetch_opts.callbacks.payload = &fetch_progress_cb_was_called;

	cl_git_pass(git_clone(&g_repo, LIVE_REPO_URL, "./foo", &g_options));

	cl_git_pass(git_buf_joinpath(&path, git_repository_workdir(g_repo), "master.txt"));
	cl_assert_equal_i(true, git_path_isfile(git_buf_cstr(&path)));

	cl_git_pass(git_reference_lookup(&head, g_repo, "HEAD"));
	cl_assert_equal_i(GIT_REFERENCE_SYMBOLIC, git_reference_type(head));
	cl_assert_equal_s("refs/heads/master", git_reference_symbolic_target(head));

	cl_assert_equal_i(true, checkout_progress_cb_was_called);
	cl_assert_equal_i(true, fetch_progress_cb_was_called);

	git_reference_free(head);
	git_buf_dispose(&path);
}