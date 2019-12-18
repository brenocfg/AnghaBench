#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  CONFLICTS_ONE_ANCESTOR_OID ; 
 int /*<<< orphan*/  CONFLICTS_ONE_OUR_OID ; 
 int /*<<< orphan*/  CONFLICTS_ONE_THEIR_OID ; 
 int /*<<< orphan*/  CONFLICTS_TWO_ANCESTOR_OID ; 
 int /*<<< orphan*/  CONFLICTS_TWO_OUR_OID ; 
 int /*<<< orphan*/  CONFLICTS_TWO_THEIR_OID ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_conflict_get (TYPE_1__ const**,TYPE_1__ const**,TYPE_1__ const**,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo_index ; 

void test_index_conflicts__get(void)
{
	const git_index_entry *conflict_entry[3];
	git_oid oid;

	cl_git_pass(git_index_conflict_get(&conflict_entry[0], &conflict_entry[1],
		&conflict_entry[2], repo_index, "conflicts-one.txt"));

	cl_assert_equal_s("conflicts-one.txt", conflict_entry[0]->path);

	git_oid_fromstr(&oid, CONFLICTS_ONE_ANCESTOR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[0]->id);

	git_oid_fromstr(&oid, CONFLICTS_ONE_OUR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[1]->id);

	git_oid_fromstr(&oid, CONFLICTS_ONE_THEIR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[2]->id);

	cl_git_pass(git_index_conflict_get(&conflict_entry[0], &conflict_entry[1],
		&conflict_entry[2], repo_index, "conflicts-two.txt"));

	cl_assert_equal_s("conflicts-two.txt", conflict_entry[0]->path);

	git_oid_fromstr(&oid, CONFLICTS_TWO_ANCESTOR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[0]->id);

	git_oid_fromstr(&oid, CONFLICTS_TWO_OUR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[1]->id);

	git_oid_fromstr(&oid, CONFLICTS_TWO_THEIR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[2]->id);
}