#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

void test_merge_workdir_simple__automerge_crlf(void)
{
#ifdef GIT_WIN32
	git_index *index;
	const git_index_entry *entry;
	git_buf automergeable_buf = GIT_BUF_INIT;

	struct merge_index_entry merge_index_entries[] = {
		ADDED_IN_MASTER_INDEX_ENTRY,
		AUTOMERGEABLE_INDEX_ENTRY,
		CHANGED_IN_BRANCH_INDEX_ENTRY,
		CHANGED_IN_MASTER_INDEX_ENTRY,

		{ 0100644, "d427e0b2e138501a3d15cc376077a3631e15bd46", 1, "conflicting.txt" },
		{ 0100644, "4e886e602529caa9ab11d71f86634bd1b6e0de10", 2, "conflicting.txt" },
		{ 0100644, "2bd0a343aeef7a2cf0d158478966a6e587ff3863", 3, "conflicting.txt" },

		UNCHANGED_INDEX_ENTRY,
	};

	struct merge_reuc_entry merge_reuc_entries[] = {
		AUTOMERGEABLE_REUC_ENTRY,
		REMOVED_IN_BRANCH_REUC_ENTRY,
		REMOVED_IN_MASTER_REUC_ENTRY
	};

	set_core_autocrlf_to(repo, true);

	merge_simple_branch(0, 0);

	cl_git_pass(git_futils_readbuffer(&automergeable_buf,
		TEST_REPO_PATH "/automergeable.txt"));
	cl_assert(strcmp(automergeable_buf.ptr, AUTOMERGEABLE_MERGED_FILE_CRLF) == 0);
	git_buf_dispose(&automergeable_buf);

	cl_assert(merge_test_index(repo_index, merge_index_entries, 8));
	cl_assert(merge_test_reuc(repo_index, merge_reuc_entries, 3));

	git_repository_index(&index, repo);

	cl_assert((entry = git_index_get_bypath(index, "automergeable.txt", 0)) != NULL);
	cl_assert(entry->file_size == strlen(AUTOMERGEABLE_MERGED_FILE_CRLF));

	git_index_free(index);
#endif /* GIT_WIN32 */
}