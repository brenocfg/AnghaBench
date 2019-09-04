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
struct TYPE_4__ {int checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int GIT_CHECKOUT_REMOVE_IGNORED ; 
 int GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_head (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_ignore_add_rule (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_ignore_path_is_ignored (int*,int /*<<< orphan*/ ,char*) ; 
 int git_path_isfile (char*) ; 

void test_checkout_tree__can_remove_ignored(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	int ignored = 0;

	opts.checkout_strategy = GIT_CHECKOUT_SAFE | GIT_CHECKOUT_REMOVE_IGNORED;

	cl_git_mkfile("testrepo/ignored_file", "as you wish");

	cl_git_pass(git_ignore_add_rule(g_repo, "ignored_file\n"));

	cl_git_pass(git_ignore_path_is_ignored(&ignored, g_repo, "ignored_file"));
	cl_assert_equal_i(1, ignored);

	cl_assert(git_path_isfile("testrepo/ignored_file"));

	cl_git_pass(git_checkout_head(g_repo, &opts));

	cl_assert(!git_path_isfile("testrepo/ignored_file"));
}