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
typedef  int /*<<< orphan*/  git_treebuilder ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  GIT_FILEMODE_TREE ; 
 int /*<<< orphan*/  assert_allowed (int /*<<< orphan*/ ) ; 
 char* blob_oid ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 char* first_tree ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_treebuilder_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_treebuilder_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_treebuilder_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_invalid_objects(bool should_allow_invalid)
{
	git_treebuilder *builder;
	git_oid valid_blob_id, invalid_blob_id, valid_tree_id, invalid_tree_id;

#define assert_allowed(expr) \
	clar__assert(!(expr) == should_allow_invalid, __FILE__, __LINE__, \
		(should_allow_invalid ? \
		 "Expected function call to succeed: " #expr : \
		 "Expected function call to fail: " #expr), \
		NULL, 1)

	cl_git_pass(git_oid_fromstr(&valid_blob_id, blob_oid));
	cl_git_pass(git_oid_fromstr(&invalid_blob_id,
		"1234567890123456789012345678901234567890"));
	cl_git_pass(git_oid_fromstr(&valid_tree_id, first_tree));
	cl_git_pass(git_oid_fromstr(&invalid_tree_id,
		"0000000000111111111122222222223333333333"));

	cl_git_pass(git_treebuilder_new(&builder, g_repo, NULL));

	/* test valid blobs and trees (these should always pass) */
	cl_git_pass(git_treebuilder_insert(NULL, builder, "file.txt", &valid_blob_id, GIT_FILEMODE_BLOB));
	cl_git_pass(git_treebuilder_insert(NULL, builder, "folder", &valid_tree_id, GIT_FILEMODE_TREE));

	/* replace valid files and folders with invalid ones */
	assert_allowed(git_treebuilder_insert(NULL, builder, "file.txt", &invalid_blob_id, GIT_FILEMODE_BLOB));
	assert_allowed(git_treebuilder_insert(NULL, builder, "folder", &invalid_blob_id, GIT_FILEMODE_BLOB));

	/* insert new invalid files and folders */
	assert_allowed(git_treebuilder_insert(NULL, builder, "invalid_file.txt", &invalid_blob_id, GIT_FILEMODE_BLOB));
	assert_allowed(git_treebuilder_insert(NULL, builder, "invalid_folder", &invalid_blob_id, GIT_FILEMODE_BLOB));

	/* insert valid blobs as trees and trees as blobs */
	assert_allowed(git_treebuilder_insert(NULL, builder, "file_as_folder", &valid_blob_id, GIT_FILEMODE_TREE));
	assert_allowed(git_treebuilder_insert(NULL, builder, "folder_as_file.txt", &valid_tree_id, GIT_FILEMODE_BLOB));

#undef assert_allowed

	git_treebuilder_free(builder);
}