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
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_reuc_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ONE_ANCESTOR_OID ; 
 int /*<<< orphan*/  ONE_OUR_OID ; 
 int /*<<< orphan*/  ONE_THEIR_OID ; 
 int /*<<< orphan*/  TWO_ANCESTOR_OID ; 
 int /*<<< orphan*/  TWO_OUR_OID ; 
 int /*<<< orphan*/  TWO_THEIR_OID ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_reuc_add (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_reuc_entrycount (int /*<<< orphan*/ ) ; 
 TYPE_1__* git_index_reuc_get_byindex (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo_index ; 

void test_index_reuc__write(void)
{
	git_oid ancestor_oid, our_oid, their_oid;
	const git_index_reuc_entry *reuc;

	git_index_clear(repo_index);

	/* Write out of order to ensure sorting is correct */
	git_oid_fromstr(&ancestor_oid, TWO_ANCESTOR_OID);
	git_oid_fromstr(&our_oid, TWO_OUR_OID);
	git_oid_fromstr(&their_oid, TWO_THEIR_OID);

	cl_git_pass(git_index_reuc_add(repo_index, "two.txt",
		0100644, &ancestor_oid,
		0100644, &our_oid,
		0100644, &their_oid));

	git_oid_fromstr(&ancestor_oid, ONE_ANCESTOR_OID);
	git_oid_fromstr(&our_oid, ONE_OUR_OID);
	git_oid_fromstr(&their_oid, ONE_THEIR_OID);

	cl_git_pass(git_index_reuc_add(repo_index, "one.txt",
		0100644, &ancestor_oid,
		0100644, &our_oid,
		0100644, &their_oid));

	cl_git_pass(git_index_write(repo_index));
	cl_assert_equal_i(2, git_index_reuc_entrycount(repo_index));

	/* ensure sort order was round-tripped correct */
	cl_assert(reuc = git_index_reuc_get_byindex(repo_index, 0));
	cl_assert_equal_s("one.txt", reuc->path);

	cl_assert(reuc = git_index_reuc_get_byindex(repo_index, 1));
	cl_assert_equal_s("two.txt", reuc->path);
}