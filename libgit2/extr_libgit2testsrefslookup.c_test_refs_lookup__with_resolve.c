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
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 scalar_t__ git_reference_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_lookup_resolved (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  git_reference_resolve (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

void test_refs_lookup__with_resolve(void)
{
	git_reference *a, *b, *temp;

	cl_git_pass(git_reference_lookup(&temp, g_repo, "HEAD"));
	cl_git_pass(git_reference_resolve(&a, temp));
	git_reference_free(temp);

	cl_git_pass(git_reference_lookup_resolved(&b, g_repo, "HEAD", 5));
	cl_assert(git_reference_cmp(a, b) == 0);
	git_reference_free(b);

	cl_git_pass(git_reference_lookup_resolved(&b, g_repo, "HEAD_TRACKER", 5));
	cl_assert(git_reference_cmp(a, b) == 0);
	git_reference_free(b);

	git_reference_free(a);
}