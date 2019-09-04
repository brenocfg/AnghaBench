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
struct TYPE_3__ {int checkout_strategy; } ;

/* Variables and functions */
 int GIT_CHECKOUT_RECREATE_MISSING ; 
 int GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  assert_name_is (char*) ; 
 TYPE_1__ checkout_opts ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 
 int /*<<< orphan*/  obj ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  symlink_or_fake (int /*<<< orphan*/ ,char*,char*) ; 

void test_checkout_icase__refuses_to_overwrite_links_for_folders(void)
{
	checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE|GIT_CHECKOUT_RECREATE_MISSING;

	cl_must_pass(symlink_or_fake(repo, "..", "testrepo/A"));

	cl_git_fail(git_checkout_tree(repo, obj, &checkout_opts));

	cl_assert(!git_path_exists("b.txt"));
	assert_name_is("testrepo/A");
}