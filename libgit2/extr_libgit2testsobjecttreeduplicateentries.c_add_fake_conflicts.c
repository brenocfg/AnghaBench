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
struct TYPE_7__ {char* path; int /*<<< orphan*/  id; void* mode; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 void* GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  GIT_INDEX_ENTRY_STAGE_SET (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_conflict_add (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 

__attribute__((used)) static void add_fake_conflicts(git_index *index)
{
	git_index_entry ancestor_entry, our_entry, their_entry;

	memset(&ancestor_entry, 0x0, sizeof(git_index_entry));
	memset(&our_entry, 0x0, sizeof(git_index_entry));
	memset(&their_entry, 0x0, sizeof(git_index_entry));

	ancestor_entry.path = "duplicate";
	ancestor_entry.mode = GIT_FILEMODE_BLOB;
	GIT_INDEX_ENTRY_STAGE_SET(&ancestor_entry, 1);
	git_oid_fromstr(&ancestor_entry.id, "a8233120f6ad708f843d861ce2b7228ec4e3dec6");

	our_entry.path = "duplicate";
	our_entry.mode = GIT_FILEMODE_BLOB;
	GIT_INDEX_ENTRY_STAGE_SET(&our_entry, 2);
	git_oid_fromstr(&our_entry.id, "45b983be36b73c0788dc9cbcb76cbb80fc7bb057");

	their_entry.path = "duplicate";
	their_entry.mode = GIT_FILEMODE_BLOB;
	GIT_INDEX_ENTRY_STAGE_SET(&their_entry, 3);
	git_oid_fromstr(&their_entry.id, "a71586c1dfe8a71c6cbf6c129f404c5642ff31bd");

	cl_git_pass(git_index_conflict_add(index, &ancestor_entry, &our_entry, &their_entry));
}