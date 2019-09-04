#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {TYPE_3__ member_0; } ;
struct TYPE_11__ {char const* member_3; int /*<<< orphan*/  id; int /*<<< orphan*/  member_2; TYPE_2__ member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ git_tree_update ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {char const* path; int /*<<< orphan*/  id; int /*<<< orphan*/  mode; TYPE_1__ member_0; } ;
typedef  TYPE_5__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  GIT_TREE_UPDATE_UPSERT ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_index_read_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write_tree_to (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_tree_create_updated (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_4__*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_object_tree_update__add_blobs_unsorted(void)
{
	git_oid tree_index_id, tree_updater_id, base_id;
	git_tree *base_tree;
	git_index *idx;
	git_index_entry entry = { {0} };
	int i;
	const char *paths[] = {
		"some/deep/path",
		"a/path/elsewhere",
		"some/other/path",
	};

	git_tree_update updates[] = {
		{ GIT_TREE_UPDATE_UPSERT, {{0}}, GIT_FILEMODE_BLOB, paths[0]},
		{ GIT_TREE_UPDATE_UPSERT, {{0}}, GIT_FILEMODE_BLOB, paths[1]},
		{ GIT_TREE_UPDATE_UPSERT, {{0}}, GIT_FILEMODE_BLOB, paths[2]},
	};

	cl_git_pass(git_oid_fromstr(&base_id, "c4dc1555e4d4fa0e0c9c3fc46734c7c35b3ce90b"));

	entry.mode = GIT_FILEMODE_BLOB;
	cl_git_pass(git_oid_fromstr(&entry.id, "fa49b077972391ad58037050f2a75f74e3671e92"));

	for (i = 0; i < 3; i++) {
		cl_git_pass(git_oid_fromstr(&updates[i].id, "fa49b077972391ad58037050f2a75f74e3671e92"));
	}

	for (i = 0; i < 2; i++) {
		int j;

		/* Create it with an index */
		cl_git_pass(git_index_new(&idx));

		base_tree = NULL;
		if (i == 1) {
			cl_git_pass(git_tree_lookup(&base_tree, g_repo, &base_id));
			cl_git_pass(git_index_read_tree(idx, base_tree));
		}

		for (j = 0; j < 3; j++) {
			entry.path = paths[j];
			cl_git_pass(git_index_add(idx, &entry));
		}

		cl_git_pass(git_index_write_tree_to(&tree_index_id, idx, g_repo));
		git_index_free(idx);

		/* Perform the same operations via the tree updater */
		cl_git_pass(git_tree_create_updated(&tree_updater_id, g_repo, base_tree, 3, updates));

		cl_assert_equal_oid(&tree_index_id, &tree_updater_id);
	}

	git_tree_free(base_tree);
}