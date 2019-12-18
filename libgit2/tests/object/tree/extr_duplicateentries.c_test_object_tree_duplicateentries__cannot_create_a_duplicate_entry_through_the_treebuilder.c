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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  GIT_FILEMODE_TREE ; 
 int /*<<< orphan*/  one_blob_and_one_tree ; 
 int /*<<< orphan*/  tree_checker (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_creator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  two_blobs ; 

void test_object_tree_duplicateentries__cannot_create_a_duplicate_entry_through_the_treebuilder(void)
{
	git_oid tid;

	tree_creator(&tid, two_blobs);
	tree_checker(&tid, "a71586c1dfe8a71c6cbf6c129f404c5642ff31bd", GIT_FILEMODE_BLOB);

	tree_creator(&tid, one_blob_and_one_tree);
	tree_checker(&tid, "4e0883eeeeebc1fb1735161cea82f7cb5fab7e63", GIT_FILEMODE_TREE);
}