#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  bld; scalar_t__ tree; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ tree_stack_entry ;
typedef  int /*<<< orphan*/  git_tree_entry ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_ERROR_TREE ; 
 int /*<<< orphan*/  GIT_FILEMODE_TREE ; 
 scalar_t__ GIT_OBJECT_TREE ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * git_tree_entry_byname (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ git_tree_entry_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_free (scalar_t__) ; 
 scalar_t__ git_treebuilder_entrycount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_treebuilder_free (int /*<<< orphan*/ ) ; 
 int git_treebuilder_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_treebuilder_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_treebuilder_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_popped_tree(tree_stack_entry *current, tree_stack_entry *popped, git_buf *component)
{
	int error;
	git_oid new_tree;

	git_tree_free(popped->tree);

	/* If the tree would be empty, remove it from the one higher up */
	if (git_treebuilder_entrycount(popped->bld) == 0) {
		git_treebuilder_free(popped->bld);
		error = git_treebuilder_remove(current->bld, popped->name);
		git__free(popped->name);
		return error;
	}

	error = git_treebuilder_write(&new_tree, popped->bld);
	git_treebuilder_free(popped->bld);

	if (error < 0) {
		git__free(popped->name);
		return error;
	}

	/* We've written out the tree, now we have to put the new value into its parent */
	git_buf_clear(component);
	git_buf_puts(component, popped->name);
	git__free(popped->name);

	GIT_ERROR_CHECK_ALLOC(component->ptr);

	/* Error out if this would create a D/F conflict in this update */
	if (current->tree) {
		const git_tree_entry *to_replace;
		to_replace = git_tree_entry_byname(current->tree, component->ptr);
		if (to_replace && git_tree_entry_type(to_replace) != GIT_OBJECT_TREE) {
			git_error_set(GIT_ERROR_TREE, "D/F conflict when updating tree");
			return -1;
		}
	}

	return git_treebuilder_insert(NULL, current->bld, component->ptr, &new_tree, GIT_FILEMODE_TREE);
}