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
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  GIT_FILEMODE_BLOB_EXECUTABLE ; 
 int /*<<< orphan*/  GIT_FILEMODE_LINK ; 
 int /*<<< orphan*/  GIT_OPT_ENABLE_STRICT_OBJECT_CREATION ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalid_id ; 
 int /*<<< orphan*/  test_add_entry (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valid_blob_id ; 
 int /*<<< orphan*/  valid_commit_id ; 
 int /*<<< orphan*/  valid_tree_id ; 

void test_index_add__invalid_entries_succeeds_by_default(void)
{
	/*
	 * Ensure that there is validation on object ids by default
	 */

	/* ensure that we can add some actually good entries */
	test_add_entry(true, valid_blob_id, GIT_FILEMODE_BLOB);
	test_add_entry(true, valid_blob_id, GIT_FILEMODE_BLOB_EXECUTABLE);
	test_add_entry(true, valid_blob_id, GIT_FILEMODE_LINK);

	/* test that we fail to add some invalid (missing) blobs and trees */
	test_add_entry(false, invalid_id, GIT_FILEMODE_BLOB);
	test_add_entry(false, invalid_id, GIT_FILEMODE_BLOB_EXECUTABLE);
	test_add_entry(false, invalid_id, GIT_FILEMODE_LINK);

	/* test that we validate the types of objects */
	test_add_entry(false, valid_commit_id, GIT_FILEMODE_BLOB);
	test_add_entry(false, valid_tree_id, GIT_FILEMODE_BLOB_EXECUTABLE);
	test_add_entry(false, valid_commit_id, GIT_FILEMODE_LINK);

	/*
	 * Ensure that there we can disable validation
	 */

	cl_git_pass(git_libgit2_opts(GIT_OPT_ENABLE_STRICT_OBJECT_CREATION, 0));

	/* ensure that we can add some actually good entries */
	test_add_entry(true, valid_blob_id, GIT_FILEMODE_BLOB);
	test_add_entry(true, valid_blob_id, GIT_FILEMODE_BLOB_EXECUTABLE);
	test_add_entry(true, valid_blob_id, GIT_FILEMODE_LINK);

	/* test that we can now add some invalid (missing) blobs and trees */
	test_add_entry(true, invalid_id, GIT_FILEMODE_BLOB);
	test_add_entry(true, invalid_id, GIT_FILEMODE_BLOB_EXECUTABLE);
	test_add_entry(true, invalid_id, GIT_FILEMODE_LINK);

	/* test that we do not validate the types of objects */
	test_add_entry(true, valid_commit_id, GIT_FILEMODE_BLOB);
	test_add_entry(true, valid_tree_id, GIT_FILEMODE_BLOB_EXECUTABLE);
	test_add_entry(true, valid_commit_id, GIT_FILEMODE_LINK);
}