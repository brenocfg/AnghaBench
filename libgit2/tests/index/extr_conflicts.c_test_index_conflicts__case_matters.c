#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_10__ {char const* path; int /*<<< orphan*/  id; void* mode; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  CONFLICTS_ONE_ANCESTOR_OID ; 
 int /*<<< orphan*/  CONFLICTS_ONE_OUR_OID ; 
 int /*<<< orphan*/  CONFLICTS_ONE_THEIR_OID ; 
 int /*<<< orphan*/  CONFLICTS_TWO_ANCESTOR_OID ; 
 int /*<<< orphan*/  CONFLICTS_TWO_OUR_OID ; 
 int /*<<< orphan*/  CONFLICTS_TWO_THEIR_OID ; 
 void* GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  GIT_INDEX_ENTRY_STAGE_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_INDEX_STAGE_ANCESTOR ; 
 int /*<<< orphan*/  GIT_INDEX_STAGE_OURS ; 
 int /*<<< orphan*/  GIT_INDEX_STAGE_THEIRS ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int cl_repo_get_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_conflict_add (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_conflict_get (TYPE_1__ const**,TYPE_1__ const**,TYPE_1__ const**,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 

void test_index_conflicts__case_matters(void)
{
	const git_index_entry *conflict_entry[3];
	git_oid oid;
	const char *upper_case = "DIFFERS-IN-CASE.TXT";
	const char *mixed_case = "Differs-In-Case.txt";
	const char *correct_case;
	bool ignorecase = cl_repo_get_bool(repo, "core.ignorecase");

	git_index_entry ancestor_entry, our_entry, their_entry;

	memset(&ancestor_entry, 0x0, sizeof(git_index_entry));
	memset(&our_entry, 0x0, sizeof(git_index_entry));
	memset(&their_entry, 0x0, sizeof(git_index_entry));

	ancestor_entry.path = upper_case;
	GIT_INDEX_ENTRY_STAGE_SET(&ancestor_entry, GIT_INDEX_STAGE_ANCESTOR);
	git_oid_fromstr(&ancestor_entry.id, CONFLICTS_ONE_ANCESTOR_OID);
	ancestor_entry.mode = GIT_FILEMODE_BLOB;

	our_entry.path = upper_case;
	GIT_INDEX_ENTRY_STAGE_SET(&our_entry, GIT_INDEX_STAGE_OURS);
	git_oid_fromstr(&our_entry.id, CONFLICTS_ONE_OUR_OID);
	our_entry.mode = GIT_FILEMODE_BLOB;

	their_entry.path = upper_case;
	GIT_INDEX_ENTRY_STAGE_SET(&their_entry, GIT_INDEX_STAGE_THEIRS);
	git_oid_fromstr(&their_entry.id, CONFLICTS_ONE_THEIR_OID);
	their_entry.mode = GIT_FILEMODE_BLOB;

	cl_git_pass(git_index_conflict_add(repo_index,
		&ancestor_entry, &our_entry, &their_entry));

	ancestor_entry.path = mixed_case;
	GIT_INDEX_ENTRY_STAGE_SET(&ancestor_entry, GIT_INDEX_STAGE_ANCESTOR);
	git_oid_fromstr(&ancestor_entry.id, CONFLICTS_TWO_ANCESTOR_OID);
	ancestor_entry.mode = GIT_FILEMODE_BLOB;

	our_entry.path = mixed_case;
	GIT_INDEX_ENTRY_STAGE_SET(&ancestor_entry, GIT_INDEX_STAGE_ANCESTOR);
	git_oid_fromstr(&our_entry.id, CONFLICTS_TWO_OUR_OID);
	ancestor_entry.mode = GIT_FILEMODE_BLOB;

	their_entry.path = mixed_case;
	GIT_INDEX_ENTRY_STAGE_SET(&their_entry, GIT_INDEX_STAGE_THEIRS);
	git_oid_fromstr(&their_entry.id, CONFLICTS_TWO_THEIR_OID);
	their_entry.mode = GIT_FILEMODE_BLOB;

	cl_git_pass(git_index_conflict_add(repo_index,
		&ancestor_entry, &our_entry, &their_entry));

	cl_git_pass(git_index_conflict_get(&conflict_entry[0], &conflict_entry[1],
		&conflict_entry[2], repo_index, upper_case));

	/*
	 * We inserted with mixed case last, so on a case-insensitive
	 * fs we should get the mixed case.
	 */
	if (ignorecase)
		correct_case = mixed_case;
	else
		correct_case = upper_case;

	cl_assert_equal_s(correct_case, conflict_entry[0]->path);
	git_oid_fromstr(&oid, ignorecase ? CONFLICTS_TWO_ANCESTOR_OID : CONFLICTS_ONE_ANCESTOR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[0]->id);

	cl_assert_equal_s(correct_case, conflict_entry[1]->path);
	git_oid_fromstr(&oid, ignorecase ? CONFLICTS_TWO_OUR_OID : CONFLICTS_ONE_OUR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[1]->id);

	cl_assert_equal_s(correct_case, conflict_entry[2]->path);
	git_oid_fromstr(&oid, ignorecase ? CONFLICTS_TWO_THEIR_OID : CONFLICTS_ONE_THEIR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[2]->id);

	cl_git_pass(git_index_conflict_get(&conflict_entry[0], &conflict_entry[1],
		&conflict_entry[2], repo_index, mixed_case));

	cl_assert_equal_s(mixed_case, conflict_entry[0]->path);
	git_oid_fromstr(&oid, CONFLICTS_TWO_ANCESTOR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[0]->id);

	cl_assert_equal_s(mixed_case, conflict_entry[1]->path);
	git_oid_fromstr(&oid, CONFLICTS_TWO_OUR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[1]->id);

	cl_assert_equal_s(mixed_case, conflict_entry[2]->path);
	git_oid_fromstr(&oid, CONFLICTS_TWO_THEIR_OID);
	cl_assert_equal_oid(&oid, &conflict_entry[2]->id);
}