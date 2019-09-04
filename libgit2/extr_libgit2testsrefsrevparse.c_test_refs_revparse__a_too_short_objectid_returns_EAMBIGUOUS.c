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
 int /*<<< orphan*/  GIT_EAMBIGUOUS ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_obj ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void test_refs_revparse__a_too_short_objectid_returns_EAMBIGUOUS(void)
{
	cl_assert_equal_i(
		GIT_EAMBIGUOUS, git_revparse_single(&g_obj, g_repo, "e90"));
}