#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_6__ {int mode; char* path; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_STATUS_CONFLICTED ; 
 int /*<<< orphan*/  GIT_STATUS_WT_MODIFIED ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_index_conflict_add (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_file (unsigned int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 

void test_status_worktree__conflicted_item(void)
{
	git_repository *repo = cl_git_sandbox_init("status");
	git_index *index;
	unsigned int status;
	git_index_entry ancestor_entry, our_entry, their_entry;

	memset(&ancestor_entry, 0x0, sizeof(git_index_entry));
	memset(&our_entry, 0x0, sizeof(git_index_entry));
	memset(&their_entry, 0x0, sizeof(git_index_entry));

	ancestor_entry.mode = 0100644;
	ancestor_entry.path = "modified_file";
	git_oid_fromstr(&ancestor_entry.id,
		"452e4244b5d083ddf0460acf1ecc74db9dcfa11a");

	our_entry.mode = 0100644;
	our_entry.path = "modified_file";
	git_oid_fromstr(&our_entry.id,
		"452e4244b5d083ddf0460acf1ecc74db9dcfa11a");

	their_entry.mode = 0100644;
	their_entry.path = "modified_file";
	git_oid_fromstr(&their_entry.id,
		"452e4244b5d083ddf0460acf1ecc74db9dcfa11a");

	cl_git_pass(git_status_file(&status, repo, "modified_file"));
	cl_assert_equal_i(GIT_STATUS_WT_MODIFIED, status);

	cl_git_pass(git_repository_index(&index, repo));
	cl_git_pass(git_index_conflict_add(index, &ancestor_entry,
		&our_entry, &their_entry));

	cl_git_pass(git_status_file(&status, repo, "modified_file"));
	cl_assert_equal_i(GIT_STATUS_CONFLICTED, status);

	git_index_free(index);
}