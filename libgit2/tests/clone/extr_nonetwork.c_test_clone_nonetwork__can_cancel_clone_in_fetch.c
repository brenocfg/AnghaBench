#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  transfer_progress; } ;
struct TYPE_6__ {TYPE_1__ callbacks; } ;
struct TYPE_7__ {char* checkout_branch; TYPE_2__ fetch_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_fixture_url (char*) ; 
 int /*<<< orphan*/  clone_cancel_fetch_transfer_progress_cb ; 
 TYPE_3__ g_options ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 

void test_clone_nonetwork__can_cancel_clone_in_fetch(void)
{
	g_options.checkout_branch = "test";

	g_options.fetch_opts.callbacks.transfer_progress =
		clone_cancel_fetch_transfer_progress_cb;

	cl_git_fail_with(git_clone(
		&g_repo, cl_git_fixture_url("testrepo.git"), "./foo", &g_options),
		-54321);

	cl_assert(!g_repo);
	cl_assert(!git_path_exists("foo/readme.txt"));
}