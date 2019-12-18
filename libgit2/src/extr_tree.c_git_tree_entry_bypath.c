#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  oid; } ;
typedef  TYPE_2__ git_tree_entry ;
struct TYPE_13__ {int /*<<< orphan*/  repo; } ;
struct TYPE_15__ {TYPE_1__ object; } ;
typedef  TYPE_3__ git_tree ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_TREE ; 
 TYPE_2__* entry_fromname (TYPE_3__ const*,char const*,size_t) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  git_tree_entry__is_tree (TYPE_2__ const*) ; 
 int git_tree_entry_dup (TYPE_2__**,TYPE_2__ const*) ; 
 int /*<<< orphan*/  git_tree_free (TYPE_3__*) ; 
 scalar_t__ git_tree_lookup (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t subpath_len (char const*) ; 

int git_tree_entry_bypath(
	git_tree_entry **entry_out,
	const git_tree *root,
	const char *path)
{
	int error = 0;
	git_tree *subtree;
	const git_tree_entry *entry;
	size_t filename_len;

	/* Find how long is the current path component (i.e.
	 * the filename between two slashes */
	filename_len = subpath_len(path);

	if (filename_len == 0) {
		git_error_set(GIT_ERROR_TREE, "invalid tree path given");
		return GIT_ENOTFOUND;
	}

	entry = entry_fromname(root, path, filename_len);

	if (entry == NULL) {
		git_error_set(GIT_ERROR_TREE,
			   "the path '%.*s' does not exist in the given tree", (int) filename_len, path);
		return GIT_ENOTFOUND;
	}

	switch (path[filename_len]) {
	case '/':
		/* If there are more components in the path...
		 * then this entry *must* be a tree */
		if (!git_tree_entry__is_tree(entry)) {
			git_error_set(GIT_ERROR_TREE,
				   "the path '%.*s' exists but is not a tree", (int) filename_len, path);
			return GIT_ENOTFOUND;
		}

		/* If there's only a slash left in the path, we
		 * return the current entry; otherwise, we keep
		 * walking down the path */
		if (path[filename_len + 1] != '\0')
			break;
		/* fall through */
	case '\0':
		/* If there are no more components in the path, return
		 * this entry */
		return git_tree_entry_dup(entry_out, entry);
	}

	if (git_tree_lookup(&subtree, root->object.repo, entry->oid) < 0)
		return -1;

	error = git_tree_entry_bypath(
		entry_out,
		subtree,
		path + filename_len + 1
	);

	git_tree_free(subtree);
	return error;
}