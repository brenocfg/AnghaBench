#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree_entry ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_7__ {int seconds; } ;
struct TYPE_6__ {int seconds; } ;
struct TYPE_8__ {int mode; char* path; int /*<<< orphan*/  id; scalar_t__ file_size; TYPE_2__ mtime; TYPE_1__ ctime; } ;
typedef  TYPE_3__ git_index_entry ;
typedef  int /*<<< orphan*/  entry ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_empty_id ; 
 int /*<<< orphan*/  g_index ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  git_index_write_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_entry_bypath (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_tree_entry_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void test_index_collision__add_blob_with_conflicting_file(void)
{
	git_index_entry entry;
	git_tree_entry *tentry;
	git_oid tree_id;
	git_tree *tree;

	memset(&entry, 0, sizeof(entry));
	entry.ctime.seconds = 12346789;
	entry.mtime.seconds = 12346789;
	entry.mode  = 0100644;
	entry.file_size = 0;
	git_oid_cpy(&entry.id, &g_empty_id);

	entry.path = "a/b";
	cl_git_pass(git_index_add(g_index, &entry));

	/* Check a/b exists here */
	cl_git_pass(git_index_write_tree(&tree_id, g_index));
	cl_git_pass(git_tree_lookup(&tree, g_repo, &tree_id));
	cl_git_pass(git_tree_entry_bypath(&tentry, tree, "a/b"));
	git_tree_entry_free(tentry);
	git_tree_free(tree);

	/* create a tree/blob collision */
	entry.path = "a/b/c";
	cl_git_pass(git_index_add(g_index, &entry));

	/* a/b should now be a tree and a/b/c a blob */
	cl_git_pass(git_index_write_tree(&tree_id, g_index));
	cl_git_pass(git_tree_lookup(&tree, g_repo, &tree_id));
	cl_git_pass(git_tree_entry_bypath(&tentry, tree, "a/b/c"));
	git_tree_entry_free(tentry);
	git_tree_free(tree);
}