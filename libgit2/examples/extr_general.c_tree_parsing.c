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
typedef  int /*<<< orphan*/  git_tree_entry ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * git_tree_entry_byindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_tree_entry_byname (int /*<<< orphan*/ *,char*) ; 
 char* git_tree_entry_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_entry_to_object (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 size_t git_tree_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void tree_parsing(git_repository *repo)
{
	const git_tree_entry *entry;
	size_t cnt;
	git_object *obj;
	git_tree *tree;
	git_oid oid;

	printf("\n*Tree Parsing*\n");

	/**
	 * Create the oid and lookup the tree object just like the other objects.
	 */
	git_oid_fromstr(&oid, "f60079018b664e4e79329a7ef9559c8d9e0378d1");
	git_tree_lookup(&tree, repo, &oid);

	/**
	 * Getting the count of entries in the tree so you can iterate over them
	 * if you want to.
	 */
	cnt = git_tree_entrycount(tree); /* 2 */
	printf("tree entries: %d\n", (int) cnt);

	entry = git_tree_entry_byindex(tree, 0);
	printf("Entry name: %s\n", git_tree_entry_name(entry)); /* "README" */

	/**
	 * You can also access tree entries by name if you know the name of the
	 * entry you're looking for.
	 */
	entry = git_tree_entry_byname(tree, "README");
	git_tree_entry_name(entry); /* "README" */

	/**
	 * Once you have the entry object, you can access the content or subtree
	 * (or commit, in the case of submodules) that it points to.  You can also
	 * get the mode if you want.
	 */
	git_tree_entry_to_object(&obj, repo, entry); /* blob */

	/**
	 * Remember to close the looked-up object and tree once you are done using it
	 */
	git_object_free(obj);
	git_tree_free(tree);
}