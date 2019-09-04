#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct seen_paths {int /*<<< orphan*/  when; int /*<<< orphan*/  who; int /*<<< orphan*/  how; int /*<<< orphan*/  what; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {struct seen_paths* notify_payload; int /*<<< orphan*/  notify_flags; int /*<<< orphan*/  notify_cb; } ;
struct TYPE_6__ {TYPE_1__ checkout_options; } ;
typedef  TYPE_2__ git_stash_apply_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_NOTIFY_ALL ; 
 TYPE_2__ GIT_STASH_APPLY_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_STATUS_CURRENT ; 
 int /*<<< orphan*/  GIT_STATUS_INDEX_NEW ; 
 int /*<<< orphan*/  GIT_STATUS_WT_MODIFIED ; 
 int /*<<< orphan*/  GIT_STATUS_WT_NEW ; 
 int /*<<< orphan*/  assert_status (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checkout_notify ; 
 int /*<<< orphan*/  cl_assert_equal_b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_has_conflicts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_stash_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 

void test_stash_apply__executes_notify_cb(void)
{
	git_stash_apply_options opts = GIT_STASH_APPLY_OPTIONS_INIT;
	struct seen_paths seen_paths = {0};

	opts.checkout_options.notify_cb = checkout_notify;
	opts.checkout_options.notify_flags = GIT_CHECKOUT_NOTIFY_ALL;
	opts.checkout_options.notify_payload = &seen_paths;

	cl_git_pass(git_stash_apply(repo, 0, &opts));

	cl_assert_equal_i(git_index_has_conflicts(repo_index), 0);
	assert_status(repo, "what", GIT_STATUS_WT_MODIFIED);
	assert_status(repo, "how", GIT_STATUS_CURRENT);
	assert_status(repo, "who", GIT_STATUS_WT_MODIFIED);
	assert_status(repo, "when", GIT_STATUS_WT_NEW);
	assert_status(repo, "why", GIT_STATUS_INDEX_NEW);
	assert_status(repo, "where", GIT_STATUS_INDEX_NEW);

	cl_assert_equal_b(true, seen_paths.what);
	cl_assert_equal_b(false, seen_paths.how);
	cl_assert_equal_b(true, seen_paths.who);
	cl_assert_equal_b(true, seen_paths.when);
}