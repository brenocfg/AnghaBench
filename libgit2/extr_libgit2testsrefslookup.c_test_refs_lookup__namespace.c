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
 int /*<<< orphan*/  GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 

void test_refs_lookup__namespace(void)
{
	int error;
	git_reference *ref;

	error = git_reference_lookup(&ref, g_repo, "refs/heads");
	cl_assert_equal_i(error, GIT_ENOTFOUND);

	error = git_reference_lookup(&ref, g_repo, "refs/heads/");
	cl_assert_equal_i(error, GIT_EINVALIDSPEC);
}