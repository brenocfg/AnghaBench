#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  test_checkout_fails (char*,char*) ; 

void test_checkout_nasty__honors_core_protecthfs(void)
{
	cl_repo_set_bool(repo, "core.protectHFS", true);

	test_checkout_fails("refs/heads/dotgit_hfs_ignorable_1", ".git/foobar");
	test_checkout_fails("refs/heads/dotgit_hfs_ignorable_2", ".git/foobar");
	test_checkout_fails("refs/heads/dotgit_hfs_ignorable_3", ".git/foobar");
	test_checkout_fails("refs/heads/dotgit_hfs_ignorable_4", ".git/foobar");
	test_checkout_fails("refs/heads/dotgit_hfs_ignorable_5", ".git/foobar");
	test_checkout_fails("refs/heads/dotgit_hfs_ignorable_6", ".git/foobar");
	test_checkout_fails("refs/heads/dotgit_hfs_ignorable_7", ".git/foobar");
	test_checkout_fails("refs/heads/dotgit_hfs_ignorable_8", ".git/foobar");
	test_checkout_fails("refs/heads/dotgit_hfs_ignorable_9", ".git/foobar");
	test_checkout_fails("refs/heads/dotgit_hfs_ignorable_10", ".git/foobar");
	test_checkout_fails("refs/heads/dotgit_hfs_ignorable_11", ".git/foobar");
	test_checkout_fails("refs/heads/dotgit_hfs_ignorable_12", ".git/foobar");
	test_checkout_fails("refs/heads/dotgit_hfs_ignorable_13", ".git/foobar");
	test_checkout_fails("refs/heads/dotgit_hfs_ignorable_14", ".git/foobar");
	test_checkout_fails("refs/heads/dotgit_hfs_ignorable_15", ".git/foobar");
	test_checkout_fails("refs/heads/dotgit_hfs_ignorable_16", ".git/foobar");
}