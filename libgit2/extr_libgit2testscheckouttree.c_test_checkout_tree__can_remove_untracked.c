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
 int GIT_CHECKOUT_REMOVE_UNTRACKED ; 
 int GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_head (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int git_path_isfile (char*) ; 

void test_checkout_tree__can_remove_untracked(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;

	opts.checkout_strategy = GIT_CHECKOUT_SAFE | GIT_CHECKOUT_REMOVE_UNTRACKED;

	cl_git_mkfile("testrepo/untracked_file", "as you wish");
	cl_assert(git_path_isfile("testrepo/untracked_file"));

	cl_git_pass(git_checkout_head(g_repo, &opts));

	cl_assert(!git_path_isfile("testrepo/untracked_file"));
}