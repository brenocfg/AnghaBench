#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* progress_payload; int /*<<< orphan*/  progress_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object ; 
 TYPE_1__ g_opts ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  progress ; 

void test_checkout_tree__calls_progress_callback(void)
{
	bool was_called = 0;

	g_opts.progress_cb = progress;
	g_opts.progress_payload = &was_called;

	cl_git_pass(git_revparse_single(&g_object, g_repo, "master"));

	cl_git_pass(git_checkout_tree(g_repo, g_object, &g_opts));

	cl_assert_equal_i(was_called, true);
}