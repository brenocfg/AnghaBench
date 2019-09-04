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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_merge_base (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_revwalk_mergebase__prefer_youngest_merge_base(void)
{
	git_oid result, one, two, expected;

	cl_git_pass(git_oid_fromstr(&one, "a4a7dce85cf63874e984719f4fdd239f5145052f"));
	cl_git_pass(git_oid_fromstr(&two, "be3563ae3f795b2b4353bcce3a527ad0a4f7f644"));
	cl_git_pass(git_oid_fromstr(&expected, "c47800c7266a2be04c571c04d5a6614691ea99bd"));

	cl_git_pass(git_merge_base(&result, _repo, &one, &two));
	cl_assert_equal_oid(&expected, &result);
}