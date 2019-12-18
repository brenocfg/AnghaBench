#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_treebuilder ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_2__ {int /*<<< orphan*/  attr; scalar_t__ filename; } ;

/* Variables and functions */
 TYPE_1__* _entries ; 
 int /*<<< orphan*/  blob_oid ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_tree_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ git_treebuilder_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_treebuilder_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_treebuilder_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_treebuilder_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_treebuilder_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_treebuilder_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_treebuilder_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  treebuilder_filter_prefixed ; 

void test_object_tree_write__filtering(void)
{
	git_treebuilder *builder;
	int i;
	git_oid entry_oid, tree_oid;
	git_tree *tree;

	git_oid_fromstr(&entry_oid, blob_oid);

	cl_git_pass(git_treebuilder_new(&builder, g_repo, NULL));

	for (i = 0; _entries[i].filename; ++i)
		cl_git_pass(git_treebuilder_insert(NULL,
			builder, _entries[i].filename, &entry_oid, _entries[i].attr));

	cl_assert_equal_i(6, (int)git_treebuilder_entrycount(builder));

	cl_assert(git_treebuilder_get(builder, "apple") != NULL);
	cl_assert(git_treebuilder_get(builder, "aardvark") != NULL);
	cl_assert(git_treebuilder_get(builder, "last") != NULL);

	git_treebuilder_filter(builder, treebuilder_filter_prefixed, "apple");

	cl_assert_equal_i(4, (int)git_treebuilder_entrycount(builder));

	cl_assert(git_treebuilder_get(builder, "apple") == NULL);
	cl_assert(git_treebuilder_get(builder, "aardvark") != NULL);
	cl_assert(git_treebuilder_get(builder, "last") != NULL);

	git_treebuilder_filter(builder, treebuilder_filter_prefixed, "a");

	cl_assert_equal_i(2, (int)git_treebuilder_entrycount(builder));

	cl_assert(git_treebuilder_get(builder, "aardvark") == NULL);
	cl_assert(git_treebuilder_get(builder, "last") != NULL);

	cl_git_pass(git_treebuilder_write(&tree_oid, builder));

	git_treebuilder_free(builder);

	cl_git_pass(git_tree_lookup(&tree, g_repo, &tree_oid));

	cl_assert_equal_i(2, (int)git_tree_entrycount(tree));

	git_tree_free(tree);
}