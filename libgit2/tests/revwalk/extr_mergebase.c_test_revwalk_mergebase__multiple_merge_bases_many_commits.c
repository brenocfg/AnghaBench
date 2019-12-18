#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ids; int /*<<< orphan*/  count; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ git_oidarray ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git__malloc (int) ; 
 int /*<<< orphan*/  git_merge_bases_many (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_oidarray_free (TYPE_1__*) ; 

void test_revwalk_mergebase__multiple_merge_bases_many_commits(void)
{
	git_oid expected1, expected2;
	git_oidarray result = {NULL, 0};

	git_oid *input = git__malloc(sizeof(git_oid) * 2);

	cl_git_pass(git_oid_fromstr(&input[0], "a4a7dce85cf63874e984719f4fdd239f5145052f"));
	cl_git_pass(git_oid_fromstr(&input[1], "be3563ae3f795b2b4353bcce3a527ad0a4f7f644"));
	cl_git_pass(git_oid_fromstr(&expected1, "c47800c7266a2be04c571c04d5a6614691ea99bd"));
	cl_git_pass(git_oid_fromstr(&expected2, "9fd738e8f7967c078dceed8190330fc8648ee56a"));

	cl_git_pass(git_merge_bases_many(&result, _repo, 2, input));
	cl_assert_equal_i(2, result.count);
	cl_assert_equal_oid(&expected1, &result.ids[0]);
	cl_assert_equal_oid(&expected2, &result.ids[1]);

	git_oidarray_free(&result);
	git__free(input);
}