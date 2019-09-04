#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_treebuilder ;
struct TYPE_4__ {int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ git_tree_entry ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_5__ {char* filename; int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 TYPE_3__* _entries ; 
 int /*<<< orphan*/  blob_oid ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* git_tree_entry_byindex (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * git_tree_entry_byname (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ git_tree_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ git_treebuilder_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_treebuilder_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_treebuilder_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_treebuilder_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_treebuilder_remove (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_treebuilder_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

void test_object_tree_write__removing_and_re_adding_in_treebuilder(void)
{
	git_treebuilder *builder;
	int i, aardvark_i, apple_i, apple_after_i, apple_extra_i, last_i;
	git_oid entry_oid, tree_oid;
	git_tree *tree;

	cl_git_pass(git_oid_fromstr(&entry_oid, blob_oid));

	cl_git_pass(git_treebuilder_new(&builder, g_repo, NULL));

	cl_assert_equal_i(0, (int)git_treebuilder_entrycount(builder));

	for (i = 0; _entries[i].filename; ++i)
		cl_git_pass(git_treebuilder_insert(NULL,
			builder, _entries[i].filename, &entry_oid, _entries[i].attr));

	cl_assert_equal_i(6, (int)git_treebuilder_entrycount(builder));

	cl_git_pass(git_treebuilder_remove(builder, "apple"));
	cl_assert_equal_i(5, (int)git_treebuilder_entrycount(builder));

	cl_git_pass(git_treebuilder_remove(builder, "apple_after"));
	cl_assert_equal_i(4, (int)git_treebuilder_entrycount(builder));

	cl_git_pass(git_treebuilder_insert(
		NULL, builder, "before_last", &entry_oid, GIT_FILEMODE_BLOB));
	cl_assert_equal_i(5, (int)git_treebuilder_entrycount(builder));

	/* reinsert apple_after */
	cl_git_pass(git_treebuilder_insert(
		NULL, builder, "apple_after", &entry_oid, GIT_FILEMODE_BLOB));
	cl_assert_equal_i(6, (int)git_treebuilder_entrycount(builder));

	cl_git_pass(git_treebuilder_remove(builder, "last"));
	cl_assert_equal_i(5, (int)git_treebuilder_entrycount(builder));

	/* reinsert last */
	cl_git_pass(git_treebuilder_insert(
		NULL, builder, "last", &entry_oid, GIT_FILEMODE_BLOB));
	cl_assert_equal_i(6, (int)git_treebuilder_entrycount(builder));

	cl_git_pass(git_treebuilder_insert(
		NULL, builder, "apple_extra", &entry_oid, GIT_FILEMODE_BLOB));
	cl_assert_equal_i(7, (int)git_treebuilder_entrycount(builder));

	cl_git_pass(git_treebuilder_write(&tree_oid, builder));

	git_treebuilder_free(builder);

	cl_git_pass(git_tree_lookup(&tree, g_repo, &tree_oid));

	cl_assert_equal_i(7, (int)git_tree_entrycount(tree));

	cl_assert(git_tree_entry_byname(tree, ".first") != NULL);
	cl_assert(git_tree_entry_byname(tree, "apple") == NULL);
	cl_assert(git_tree_entry_byname(tree, "apple_after") != NULL);
	cl_assert(git_tree_entry_byname(tree, "apple_extra") != NULL);
	cl_assert(git_tree_entry_byname(tree, "last") != NULL);

	aardvark_i = apple_i = apple_after_i = apple_extra_i = last_i = -1;

	for (i = 0; i < 7; ++i) {
		const git_tree_entry *entry = git_tree_entry_byindex(tree, i);

		if (!strcmp(entry->filename, "aardvark"))
			aardvark_i = i;
		else if (!strcmp(entry->filename, "apple"))
			apple_i = i;
		else if (!strcmp(entry->filename, "apple_after"))
			apple_after_i = i;
		else if (!strcmp(entry->filename, "apple_extra"))
			apple_extra_i = i;
		else if (!strcmp(entry->filename, "last"))
			last_i = i;
	}

	cl_assert_equal_i(-1, apple_i);
	cl_assert_equal_i(6, last_i);
	cl_assert(aardvark_i < apple_after_i);
	cl_assert(apple_after_i < apple_extra_i);

	git_tree_free(tree);
}