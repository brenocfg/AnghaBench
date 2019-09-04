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
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 

void test_refs_read__chomped(void)
{
	git_reference *test, *chomped;

	cl_git_pass(git_reference_lookup(&test, g_repo, "refs/heads/test"));
	cl_git_pass(git_reference_lookup(&chomped, g_repo, "refs/heads/chomped"));
	cl_assert_equal_oid(git_reference_target(test), git_reference_target(chomped));

	git_reference_free(test);
	git_reference_free(chomped);
}