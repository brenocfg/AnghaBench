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
 int /*<<< orphan*/  GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_reflog_rename (int /*<<< orphan*/ ,char*,char*) ; 

void test_refs_reflog_reflog__renaming_with_an_invalid_name_returns_EINVALIDSPEC(void)
{
	cl_assert_equal_i(GIT_EINVALIDSPEC,
			  git_reflog_rename(g_repo, "refs/heads/master", "refs/heads/Inv@{id"));
}