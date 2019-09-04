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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void test_refs_read__unfound_return_ENOTFOUND(void)
{
	git_reference *reference;
	git_oid id;

	cl_assert_equal_i(GIT_ENOTFOUND,
		git_reference_lookup(&reference, g_repo, "TEST_MASTER"));
	cl_assert_equal_i(GIT_ENOTFOUND,
		git_reference_lookup(&reference, g_repo, "refs/test/master"));
	cl_assert_equal_i(GIT_ENOTFOUND,
		git_reference_lookup(&reference, g_repo, "refs/tags/test/master"));
	cl_assert_equal_i(GIT_ENOTFOUND,
		git_reference_lookup(&reference, g_repo, "refs/tags/test/farther/master"));

	cl_assert_equal_i(GIT_ENOTFOUND,
		git_reference_name_to_id(&id, g_repo, "refs/tags/test/farther/master"));
}