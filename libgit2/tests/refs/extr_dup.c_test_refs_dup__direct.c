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
 scalar_t__ g_repo ; 
 scalar_t__ git_reference_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_dup (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,scalar_t__,char*) ; 
 scalar_t__ git_reference_owner (int /*<<< orphan*/ *) ; 

void test_refs_dup__direct(void)
{
	git_reference *a, *b;

	cl_git_pass(git_reference_lookup(&a, g_repo, "refs/heads/master"));
	cl_git_pass(git_reference_dup(&b, a));

	cl_assert(git_reference_cmp(a, b) == 0);
	cl_assert(git_reference_owner(b) == g_repo);

	git_reference_free(b);
	git_reference_free(a);
}