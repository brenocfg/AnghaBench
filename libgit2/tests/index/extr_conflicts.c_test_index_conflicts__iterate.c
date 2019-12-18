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
struct TYPE_5__ {int /*<<< orphan*/  path; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index_conflict_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  CONFLICTS_ONE_ANCESTOR_OID ; 
 int /*<<< orphan*/  CONFLICTS_ONE_OUR_OID ; 
 int /*<<< orphan*/  CONFLICTS_ONE_THEIR_OID ; 
 int /*<<< orphan*/  CONFLICTS_TWO_ANCESTOR_OID ; 
 int /*<<< orphan*/  CONFLICTS_TWO_OUR_OID ; 
 int /*<<< orphan*/  CONFLICTS_TWO_THEIR_OID ; 
 scalar_t__ GIT_ITEROVER ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (scalar_t__) ; 
 scalar_t__ git__strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_conflict_iterator_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_index_conflict_iterator_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ git_index_conflict_next (TYPE_1__ const**,TYPE_1__ const**,TYPE_1__ const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo_index ; 

void test_index_conflicts__iterate(void)
{
	git_index_conflict_iterator *iterator;
	const git_index_entry *conflict_entry[3];
	git_oid oid;

	cl_git_pass(git_index_conflict_iterator_new(&iterator, repo_index));

	cl_git_pass(git_index_conflict_next(&conflict_entry[0], &conflict_entry[1], &conflict_entry[2], iterator));

	git_oid_fromstr(&oid, CONFLICTS_ONE_ANCESTOR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[0]->id);
	cl_assert(git__strcmp(conflict_entry[0]->path, "conflicts-one.txt") == 0);

	git_oid_fromstr(&oid, CONFLICTS_ONE_OUR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[1]->id);
	cl_assert(git__strcmp(conflict_entry[0]->path, "conflicts-one.txt") == 0);

	git_oid_fromstr(&oid, CONFLICTS_ONE_THEIR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[2]->id);
	cl_assert(git__strcmp(conflict_entry[0]->path, "conflicts-one.txt") == 0);

	cl_git_pass(git_index_conflict_next(&conflict_entry[0], &conflict_entry[1], &conflict_entry[2], iterator));

	git_oid_fromstr(&oid, CONFLICTS_TWO_ANCESTOR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[0]->id);
	cl_assert(git__strcmp(conflict_entry[0]->path, "conflicts-two.txt") == 0);

	git_oid_fromstr(&oid, CONFLICTS_TWO_OUR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[1]->id);
	cl_assert(git__strcmp(conflict_entry[0]->path, "conflicts-two.txt") == 0);

	git_oid_fromstr(&oid, CONFLICTS_TWO_THEIR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[2]->id);
	cl_assert(git__strcmp(conflict_entry[0]->path, "conflicts-two.txt") == 0);

	cl_assert(git_index_conflict_next(&conflict_entry[0], &conflict_entry[1], &conflict_entry[2], iterator) == GIT_ITEROVER);

	cl_assert(conflict_entry[0] == NULL);
	cl_assert(conflict_entry[2] == NULL);
	cl_assert(conflict_entry[2] == NULL);

	git_index_conflict_iterator_free(iterator);
}