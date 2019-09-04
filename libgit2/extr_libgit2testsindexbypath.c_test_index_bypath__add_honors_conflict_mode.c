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
struct TYPE_6__ {char* path; int flags; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB_EXECUTABLE ; 
 int GIT_INDEX_ENTRY_STAGESHIFT ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_idx ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_remove_bypath (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  p_chmod (char*,int /*<<< orphan*/ ) ; 

void test_index_bypath__add_honors_conflict_mode(void)
{
	const git_index_entry *entry;
	git_index_entry new_entry;
	int stage = 0;

	cl_assert((entry = git_index_get_bypath(g_idx, "README.txt", 0)) != NULL);

	memcpy(&new_entry, entry, sizeof(git_index_entry));
	new_entry.path = "README.txt";
	new_entry.mode = GIT_FILEMODE_BLOB_EXECUTABLE;

	cl_must_pass(p_chmod("submod2/README.txt", GIT_FILEMODE_BLOB_EXECUTABLE));

	cl_git_pass(git_index_remove_bypath(g_idx, "README.txt"));

	for (stage = 1; stage <= 3; stage++) {
		new_entry.flags = stage << GIT_INDEX_ENTRY_STAGESHIFT;
		cl_git_pass(git_index_add(g_idx, &new_entry));
	}

	cl_git_pass(git_index_write(g_idx));

	cl_git_rewritefile("submod2/README.txt", "Modified but still executable");

	cl_git_pass(git_index_add_bypath(g_idx, "README.txt"));
	cl_git_pass(git_index_write(g_idx));

	cl_assert((entry = git_index_get_bypath(g_idx, "README.txt", 0)) != NULL);
	cl_assert_equal_i(GIT_FILEMODE_BLOB_EXECUTABLE, entry->mode);
}