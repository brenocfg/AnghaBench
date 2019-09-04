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
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_4__ {int /*<<< orphan*/ * ids; int /*<<< orphan*/  count; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ git_oidarray ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_merge_bases (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_oidarray_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_revwalk_mergebase__remove_redundant(void)
{
	git_repository *repo;
	git_oid one, two, base;
	git_oidarray result = {NULL, 0};

	cl_git_pass(git_repository_open(&repo, cl_fixture("redundant.git")));

	cl_git_pass(git_oid_fromstr(&one, "d89137c93ba1ee749214ff4ce52ae9137bc833f9"));
	cl_git_pass(git_oid_fromstr(&two, "91f4b95df4a59504a9813ba66912562931d990e3"));
	cl_git_pass(git_oid_fromstr(&base, "6cb1f2352d974e1c5a776093017e8772416ac97a"));

	cl_git_pass(git_merge_bases(&result, repo, &one, &two));
	cl_assert_equal_i(1, result.count);
	cl_assert_equal_oid(&base, &result.ids[0]);

	git_oidarray_free(&result);
	git_repository_free(repo);
}