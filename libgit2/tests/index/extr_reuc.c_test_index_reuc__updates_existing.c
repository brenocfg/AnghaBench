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
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_4__ {int /*<<< orphan*/ * oid; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_reuc_entry ;

/* Variables and functions */
 int GIT_INDEX_CAPABILITY_IGNORE_CASE ; 
 int /*<<< orphan*/  TWO_ANCESTOR_OID ; 
 int /*<<< orphan*/  TWO_OUR_OID ; 
 int /*<<< orphan*/  TWO_THEIR_OID ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int git_index_caps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_reuc_add (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_reuc_entrycount (int /*<<< orphan*/ ) ; 
 TYPE_1__* git_index_reuc_get_byindex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_set_caps (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo_index ; 

void test_index_reuc__updates_existing(void)
{
	const git_index_reuc_entry *reuc;
	git_oid ancestor_oid, our_oid, their_oid, oid;
	int index_caps;

	git_index_clear(repo_index);

	index_caps = git_index_caps(repo_index);

	index_caps |= GIT_INDEX_CAPABILITY_IGNORE_CASE;
	cl_git_pass(git_index_set_caps(repo_index, index_caps));

	git_oid_fromstr(&ancestor_oid, TWO_ANCESTOR_OID);
	git_oid_fromstr(&our_oid, TWO_OUR_OID);
	git_oid_fromstr(&their_oid, TWO_THEIR_OID);

	cl_git_pass(git_index_reuc_add(repo_index, "two.txt",
		0100644, &ancestor_oid,
		0100644, &our_oid,
		0100644, &their_oid));

	cl_git_pass(git_index_reuc_add(repo_index, "TWO.txt",
		0100644, &our_oid,
		0100644, &their_oid,
		0100644, &ancestor_oid));

	cl_assert_equal_i(1, git_index_reuc_entrycount(repo_index));

	cl_assert(reuc = git_index_reuc_get_byindex(repo_index, 0));

	cl_assert_equal_s("TWO.txt", reuc->path);
	git_oid_fromstr(&oid, TWO_OUR_OID);
	cl_assert_equal_oid(&reuc->oid[0], &oid);
	git_oid_fromstr(&oid, TWO_THEIR_OID);
	cl_assert_equal_oid(&reuc->oid[1], &oid);
	git_oid_fromstr(&oid, TWO_ANCESTOR_OID);
	cl_assert_equal_oid(&reuc->oid[2], &oid);
}