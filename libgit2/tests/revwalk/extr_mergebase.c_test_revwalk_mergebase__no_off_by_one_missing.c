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
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_merge_base (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_revwalk_mergebase__no_off_by_one_missing(void)
{
	git_oid result, one, two;

	cl_git_pass(git_oid_fromstr(&one, "1a443023183e3f2bfbef8ac923cd81c1018a18fd"));
	cl_git_pass(git_oid_fromstr(&two, "9f13f7d0a9402c681f91dc590cf7b5470e6a77d2"));
	cl_git_pass(git_merge_base(&result, _repo, &one, &two));
}