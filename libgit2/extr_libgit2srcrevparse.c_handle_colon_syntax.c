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
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int GIT_EINVALIDSPEC ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_OBJECT_TREE ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_owner (int /*<<< orphan*/ *) ; 
 int git_object_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_tree_entry_bypath (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_tree_entry_free (int /*<<< orphan*/ *) ; 
 int git_tree_entry_to_object (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_colon_syntax(
	git_object **out,
	git_object *obj,
	const char *path)
{
	git_object *tree;
	int error = -1;
	git_tree_entry *entry = NULL;

	if ((error = git_object_peel(&tree, obj, GIT_OBJECT_TREE)) < 0)
		return error == GIT_ENOTFOUND ? GIT_EINVALIDSPEC : error;

	if (*path == '\0') {
		*out = tree;
		return 0;
	}

	/*
	 * TODO: Handle the relative path syntax
	 * (:./relative/path and :../relative/path)
	 */
	if ((error = git_tree_entry_bypath(&entry, (git_tree *)tree, path)) < 0)
		goto cleanup;

	error = git_tree_entry_to_object(out, git_object_owner(tree), entry);

cleanup:
	git_tree_entry_free(entry);
	git_object_free(tree);

	return error;
}