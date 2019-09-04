#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* path; int mode; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  CONFLICTS_ONE_ANCESTOR_OID ; 
 int /*<<< orphan*/  CONFLICTS_ONE_OUR_OID ; 
 int /*<<< orphan*/  CONFLICTS_ONE_THEIR_OID ; 
 int /*<<< orphan*/  GIT_INDEX_ENTRY_STAGE_SET (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_conflict_add (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int git_index_entrycount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  repo_index ; 

void test_index_conflicts__add(void)
{
	git_index_entry ancestor_entry, our_entry, their_entry;

	cl_assert(git_index_entrycount(repo_index) == 8);

	memset(&ancestor_entry, 0x0, sizeof(git_index_entry));
	memset(&our_entry, 0x0, sizeof(git_index_entry));
	memset(&their_entry, 0x0, sizeof(git_index_entry));

	ancestor_entry.path = "test-one.txt";
	ancestor_entry.mode = 0100644;
	GIT_INDEX_ENTRY_STAGE_SET(&ancestor_entry, 1);
	git_oid_fromstr(&ancestor_entry.id, CONFLICTS_ONE_ANCESTOR_OID);

	our_entry.path = "test-one.txt";
	our_entry.mode = 0100644;
	GIT_INDEX_ENTRY_STAGE_SET(&our_entry, 2);
	git_oid_fromstr(&our_entry.id, CONFLICTS_ONE_OUR_OID);

	their_entry.path = "test-one.txt";
	their_entry.mode = 0100644;
	GIT_INDEX_ENTRY_STAGE_SET(&ancestor_entry, 2);
	git_oid_fromstr(&their_entry.id, CONFLICTS_ONE_THEIR_OID);

	cl_git_pass(git_index_conflict_add(repo_index, &ancestor_entry, &our_entry, &their_entry));

	cl_assert(git_index_entrycount(repo_index) == 11);
}