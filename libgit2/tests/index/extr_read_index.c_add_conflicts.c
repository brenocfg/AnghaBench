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
struct TYPE_7__ {char const* path; int mode; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 char* CONFLICTS_ONE_ANCESTOR_OID ; 
 char* CONFLICTS_ONE_OUR_OID ; 
 char* CONFLICTS_ONE_THEIR_OID ; 
 char* CONFLICTS_TWO_ANCESTOR_OID ; 
 char* CONFLICTS_TWO_OUR_OID ; 
 char* CONFLICTS_TWO_THEIR_OID ; 
 int /*<<< orphan*/  GIT_INDEX_ENTRY_STAGE_SET (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_conflict_add (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 

__attribute__((used)) static void add_conflicts(git_index *index, const char *filename)
{
	git_index_entry ancestor_entry, our_entry, their_entry;
	static int conflict_idx = 0;
	char *ancestor_ids[] =
		{ CONFLICTS_ONE_ANCESTOR_OID, CONFLICTS_TWO_ANCESTOR_OID };
	char *our_ids[] =
		{ CONFLICTS_ONE_OUR_OID, CONFLICTS_TWO_OUR_OID };
	char *their_ids[] =
		{ CONFLICTS_ONE_THEIR_OID, CONFLICTS_TWO_THEIR_OID };

	conflict_idx = (conflict_idx + 1) % 2;

	memset(&ancestor_entry, 0x0, sizeof(git_index_entry));
	memset(&our_entry, 0x0, sizeof(git_index_entry));
	memset(&their_entry, 0x0, sizeof(git_index_entry));

	ancestor_entry.path = filename;
	ancestor_entry.mode = 0100644;
	GIT_INDEX_ENTRY_STAGE_SET(&ancestor_entry, 1);
	git_oid_fromstr(&ancestor_entry.id, ancestor_ids[conflict_idx]);

	our_entry.path = filename;
	our_entry.mode = 0100644;
	GIT_INDEX_ENTRY_STAGE_SET(&our_entry, 2);
	git_oid_fromstr(&our_entry.id, our_ids[conflict_idx]);

	their_entry.path = filename;
	their_entry.mode = 0100644;
	GIT_INDEX_ENTRY_STAGE_SET(&ancestor_entry, 2);
	git_oid_fromstr(&their_entry.id, their_ids[conflict_idx]);

	cl_git_pass(git_index_conflict_add(index, &ancestor_entry,
		&our_entry, &their_entry));
}