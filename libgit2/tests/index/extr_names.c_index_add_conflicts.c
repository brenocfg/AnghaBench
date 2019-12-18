#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {char const* path; int /*<<< orphan*/  id; void* mode; TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_index_entry ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const***) ; 
 void* GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  GIT_INDEX_ENTRY_STAGE_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_INDEX_STAGE_ANCESTOR ; 
 int /*<<< orphan*/  GIT_INDEX_STAGE_OURS ; 
 int /*<<< orphan*/  GIT_INDEX_STAGE_THEIRS ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  repo_index ; 

__attribute__((used)) static void index_add_conflicts(void)
{
	git_index_entry entry = {{0}};
	const char *paths[][3] = {
		{ "ancestor", "ours", "theirs" },
		{ "ancestor2", "ours2", "theirs2" },
		{ "ancestor3", "ours3", "theirs3" } };
	const char **conflict;
	size_t i;

	for (i = 0; i < ARRAY_SIZE(paths); i++) {
		conflict = paths[i];

		/* ancestor */
		entry.path = conflict[0];
		entry.mode = GIT_FILEMODE_BLOB;
		GIT_INDEX_ENTRY_STAGE_SET(&entry, GIT_INDEX_STAGE_ANCESTOR);
		git_oid_fromstr(&entry.id, "1f85ca51b8e0aac893a621b61a9c2661d6aa6d81");
		cl_git_pass(git_index_add(repo_index, &entry));

		/* ours */
		entry.path = conflict[1];
		entry.mode = GIT_FILEMODE_BLOB;
		GIT_INDEX_ENTRY_STAGE_SET(&entry, GIT_INDEX_STAGE_OURS);
		git_oid_fromstr(&entry.id, "1f85ca51b8e0aac893a621b61a9c2661d6aa6d81");
		cl_git_pass(git_index_add(repo_index, &entry));

		/* theirs */
		entry.path = conflict[2];
		entry.mode = GIT_FILEMODE_BLOB;
		GIT_INDEX_ENTRY_STAGE_SET(&entry, GIT_INDEX_STAGE_THEIRS);
		git_oid_fromstr(&entry.id, "1f85ca51b8e0aac893a621b61a9c2661d6aa6d81");
		cl_git_pass(git_index_add(repo_index, &entry));
	}
}