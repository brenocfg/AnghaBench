#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_6__ {int* payload; int /*<<< orphan*/ * transfer_progress; } ;
struct TYPE_7__ {TYPE_1__ callbacks; } ;
struct TYPE_8__ {int bare; int /*<<< orphan*/  remote_cb; TYPE_2__ fetch_opts; } ;
typedef  TYPE_3__ git_clone_options ;

/* Variables and functions */
 TYPE_3__ GIT_CLONE_OPTIONS_INIT ; 
 int GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  LIVE_REPO_URL ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_progress ; 
 int /*<<< orphan*/ * g_repo ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reference_symbolic_target (int /*<<< orphan*/ *) ; 
 int git_reference_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remote_mirror_cb ; 

void test_online_clone__clone_mirror(void)
{
	git_clone_options opts = GIT_CLONE_OPTIONS_INIT;
	git_reference *head;

	bool fetch_progress_cb_was_called = false;

	opts.fetch_opts.callbacks.transfer_progress = &fetch_progress;
	opts.fetch_opts.callbacks.payload = &fetch_progress_cb_was_called;

	opts.bare = true;
	opts.remote_cb = remote_mirror_cb;

	cl_git_pass(git_clone(&g_repo, LIVE_REPO_URL, "./foo.git", &opts));

	cl_git_pass(git_reference_lookup(&head, g_repo, "HEAD"));
	cl_assert_equal_i(GIT_REFERENCE_SYMBOLIC, git_reference_type(head));
	cl_assert_equal_s("refs/heads/master", git_reference_symbolic_target(head));

	cl_assert_equal_i(true, fetch_progress_cb_was_called);

	git_reference_free(head);
	git_repository_free(g_repo);
	g_repo = NULL;

	cl_fixture_cleanup("./foo.git");
}