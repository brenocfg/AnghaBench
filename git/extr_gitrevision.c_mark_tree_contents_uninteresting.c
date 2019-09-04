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
struct tree_desc {int dummy; } ;
struct tree {int /*<<< orphan*/  size; int /*<<< orphan*/  buffer; } ;
struct repository {int dummy; } ;
struct name_entry {int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
#define  OBJ_BLOB 129 
#define  OBJ_TREE 128 
 int /*<<< orphan*/  free_tree_buffer (struct tree*) ; 
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_blob (struct repository*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lookup_tree (struct repository*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_blob_uninteresting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_tree_uninteresting (struct repository*,int /*<<< orphan*/ ) ; 
 int object_type (int /*<<< orphan*/ ) ; 
 scalar_t__ parse_tree_gently (struct tree*,int) ; 
 scalar_t__ tree_entry (struct tree_desc*,struct name_entry*) ; 

__attribute__((used)) static void mark_tree_contents_uninteresting(struct repository *r,
					     struct tree *tree)
{
	struct tree_desc desc;
	struct name_entry entry;

	if (parse_tree_gently(tree, 1) < 0)
		return;

	init_tree_desc(&desc, tree->buffer, tree->size);
	while (tree_entry(&desc, &entry)) {
		switch (object_type(entry.mode)) {
		case OBJ_TREE:
			mark_tree_uninteresting(r, lookup_tree(r, &entry.oid));
			break;
		case OBJ_BLOB:
			mark_blob_uninteresting(lookup_blob(r, &entry.oid));
			break;
		default:
			/* Subproject commit - not in this repository */
			break;
		}
	}

	/*
	 * We don't care about the tree any more
	 * after it has been marked uninteresting.
	 */
	free_tree_buffer(tree);
}