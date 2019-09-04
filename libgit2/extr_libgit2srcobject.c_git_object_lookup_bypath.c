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
typedef  scalar_t__ git_object_t ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_ERROR_OBJECT ; 
 scalar_t__ GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  GIT_OBJECT_TREE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  git_object_owner (int /*<<< orphan*/  const*) ; 
 int git_object_peel (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int git_tree_entry_bypath (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_tree_entry_free (int /*<<< orphan*/ *) ; 
 int git_tree_entry_to_object (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ git_tree_entry_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

int git_object_lookup_bypath(
		git_object **out,
		const git_object *treeish,
		const char *path,
		git_object_t type)
{
	int error = -1;
	git_tree *tree = NULL;
	git_tree_entry *entry = NULL;

	assert(out && treeish && path);

	if ((error = git_object_peel((git_object**)&tree, treeish, GIT_OBJECT_TREE)) < 0 ||
		 (error = git_tree_entry_bypath(&entry, tree, path)) < 0)
	{
		goto cleanup;
	}

	if (type != GIT_OBJECT_ANY && git_tree_entry_type(entry) != type)
	{
		git_error_set(GIT_ERROR_OBJECT,
				"object at path '%s' is not of the asked-for type %d",
				path, type);
		error = GIT_EINVALIDSPEC;
		goto cleanup;
	}

	error = git_tree_entry_to_object(out, git_object_owner(treeish), entry);

cleanup:
	git_tree_entry_free(entry);
	git_tree_free(tree);
	return error;
}