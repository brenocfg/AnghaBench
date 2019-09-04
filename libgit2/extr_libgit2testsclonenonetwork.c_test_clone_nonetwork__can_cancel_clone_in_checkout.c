#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* notify_payload; int /*<<< orphan*/  notify_cb; int /*<<< orphan*/  notify_flags; } ;
struct TYPE_5__ {char* checkout_branch; TYPE_1__ checkout_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_NOTIFY_UPDATED ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_fixture_url (char*) ; 
 int /*<<< orphan*/  clone_cancel_checkout_cb ; 
 TYPE_2__ g_options ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 

void test_clone_nonetwork__can_cancel_clone_in_checkout(void)
{
	g_options.checkout_branch = "test";

	g_options.checkout_opts.notify_flags = GIT_CHECKOUT_NOTIFY_UPDATED;
	g_options.checkout_opts.notify_cb = clone_cancel_checkout_cb;
	g_options.checkout_opts.notify_payload = "readme.txt";

	cl_git_fail_with(git_clone(
		&g_repo, cl_git_fixture_url("testrepo.git"), "./foo", &g_options),
		-12345);

	cl_assert(!g_repo);
	cl_assert(!git_path_exists("foo/readme.txt"));
}