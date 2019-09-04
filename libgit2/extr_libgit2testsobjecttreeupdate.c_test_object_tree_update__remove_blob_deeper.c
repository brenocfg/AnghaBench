#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {TYPE_1__ member_0; } ;
struct TYPE_7__ {char const* member_3; int /*<<< orphan*/  member_2; TYPE_2__ member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ git_tree_update ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  GIT_TREE_UPDATE_REMOVE ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_index_read_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_remove (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_write_tree_to (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_tree_create_updated (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_object_tree_update__remove_blob_deeper(void)
{
	git_oid tree_index_id, tree_updater_id, base_id;
	git_tree *base_tree;
	git_index *idx;
	const char *path = "subdir/README";

	git_tree_update updates[] = {
		{ GIT_TREE_UPDATE_REMOVE, {{0}}, GIT_FILEMODE_BLOB /* ignored */, path},
	};

	cl_git_pass(git_oid_fromstr(&base_id, "c4dc1555e4d4fa0e0c9c3fc46734c7c35b3ce90b"));
	cl_git_pass(git_tree_lookup(&base_tree, g_repo, &base_id));

	/* Create it with an index */
	cl_git_pass(git_index_new(&idx));
	cl_git_pass(git_index_read_tree(idx, base_tree));
	cl_git_pass(git_index_remove(idx, path, 0));
	cl_git_pass(git_index_write_tree_to(&tree_index_id, idx, g_repo));
	git_index_free(idx);

	/* Perform the same operation via the tree updater */
	cl_git_pass(git_tree_create_updated(&tree_updater_id, g_repo, base_tree, 1, updates));

	cl_assert_equal_oid(&tree_index_id, &tree_updater_id);

	git_tree_free(base_tree);
}