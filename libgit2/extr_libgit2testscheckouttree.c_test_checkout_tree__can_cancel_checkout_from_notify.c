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
struct checkout_cancel_at {char* filename; int error; scalar_t__ count; } ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_4__ {int /*<<< orphan*/  checkout_strategy; struct checkout_cancel_at* notify_payload; int /*<<< orphan*/  notify_cb; int /*<<< orphan*/  notify_flags; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 int /*<<< orphan*/  GIT_CHECKOUT_NOTIFY_UPDATED ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  assert_on_branch (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  checkout_cancel_cb ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,scalar_t__) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_path_exists (char*) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void test_checkout_tree__can_cancel_checkout_from_notify(void)
{
	struct checkout_cancel_at ca;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_oid oid;
	git_object *obj = NULL;

	assert_on_branch(g_repo, "master");

	cl_git_pass(git_reference_name_to_id(&oid, g_repo, "refs/heads/dir"));
	cl_git_pass(git_object_lookup(&obj, g_repo, &oid, GIT_OBJECT_ANY));

	ca.filename = "new.txt";
	ca.error = -5555;
	ca.count = 0;

	opts.notify_flags = GIT_CHECKOUT_NOTIFY_UPDATED;
	opts.notify_cb = checkout_cancel_cb;
	opts.notify_payload = &ca;
	opts.checkout_strategy = GIT_CHECKOUT_FORCE;

	cl_assert(!git_path_exists("testrepo/new.txt"));

	cl_git_fail_with(git_checkout_tree(g_repo, obj, &opts), -5555);

	cl_assert(!git_path_exists("testrepo/new.txt"));

	/* on case-insensitive FS = a/b.txt, branch_file.txt, new.txt */
	/* on case-sensitive FS   = README, then above */

	if (git_path_exists("testrepo/.git/CoNfIg")) /* case insensitive */
		cl_assert_equal_i(3, ca.count);
	else
		cl_assert_equal_i(4, ca.count);

	/* and again with a different stopping point and return code */
	ca.filename = "README";
	ca.error = 123;
	ca.count = 0;

	cl_git_fail_with(git_checkout_tree(g_repo, obj, &opts), 123);

	cl_assert(!git_path_exists("testrepo/new.txt"));

	if (git_path_exists("testrepo/.git/CoNfIg")) /* case insensitive */
		cl_assert_equal_i(4, ca.count);
	else
		cl_assert_equal_i(1, ca.count);

	git_object_free(obj);
}