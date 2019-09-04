#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tree_desc {int dummy; } ;
struct TYPE_3__ {int flags; } ;
struct tree {TYPE_1__ object; int /*<<< orphan*/  size; int /*<<< orphan*/  buffer; } ;
struct repository {int dummy; } ;
struct name_entry {int /*<<< orphan*/  oid; int /*<<< orphan*/  path; int /*<<< orphan*/  mode; } ;
struct hashmap {int dummy; } ;
struct TYPE_4__ {int flags; } ;
struct blob {TYPE_2__ object; } ;

/* Variables and functions */
#define  OBJ_BLOB 129 
#define  OBJ_TREE 128 
 int UNINTERESTING ; 
 int /*<<< orphan*/  free_tree_buffer (struct tree*) ; 
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct blob* lookup_blob (struct repository*,int /*<<< orphan*/ *) ; 
 struct tree* lookup_tree (struct repository*,int /*<<< orphan*/ *) ; 
 int object_type (int /*<<< orphan*/ ) ; 
 scalar_t__ parse_tree_gently (struct tree*,int) ; 
 int /*<<< orphan*/  paths_and_oids_insert (struct hashmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ tree_entry (struct tree_desc*,struct name_entry*) ; 

__attribute__((used)) static void add_children_by_path(struct repository *r,
				 struct tree *tree,
				 struct hashmap *map)
{
	struct tree_desc desc;
	struct name_entry entry;

	if (!tree)
		return;

	if (parse_tree_gently(tree, 1) < 0)
		return;

	init_tree_desc(&desc, tree->buffer, tree->size);
	while (tree_entry(&desc, &entry)) {
		switch (object_type(entry.mode)) {
		case OBJ_TREE:
			paths_and_oids_insert(map, entry.path, &entry.oid);

			if (tree->object.flags & UNINTERESTING) {
				struct tree *child = lookup_tree(r, &entry.oid);
				if (child)
					child->object.flags |= UNINTERESTING;
			}
			break;
		case OBJ_BLOB:
			if (tree->object.flags & UNINTERESTING) {
				struct blob *child = lookup_blob(r, &entry.oid);
				if (child)
					child->object.flags |= UNINTERESTING;
			}
			break;
		default:
			/* Subproject commit - not in this repository */
			break;
		}
	}

	free_tree_buffer(tree);
}