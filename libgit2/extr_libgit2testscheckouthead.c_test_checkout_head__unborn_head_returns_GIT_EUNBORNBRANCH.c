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
 int /*<<< orphan*/  GIT_EUNBORNBRANCH ; 
 int /*<<< orphan*/  NON_EXISTING_HEAD ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_head (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_head_unborn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_checkout_head__unborn_head_returns_GIT_EUNBORNBRANCH(void)
{
	make_head_unborn(g_repo, NON_EXISTING_HEAD);

	cl_assert_equal_i(GIT_EUNBORNBRANCH, git_checkout_head(g_repo, NULL));
}