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
struct object {int flags; int /*<<< orphan*/  oid; } ;
struct tree {int /*<<< orphan*/  size; int /*<<< orphan*/  buffer; struct object object; } ;
struct object_list {int dummy; } ;
struct name_entry {int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int LOCAL ; 
#define  OBJ_BLOB 129 
#define  OBJ_TREE 128 
 int SEEN ; 
 int UNINTERESTING ; 
 struct object_list** add_one_object (struct object*,struct object_list**) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_tree_buffer (struct tree*) ; 
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tree* lookup_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int object_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_tree (struct tree*) ; 
 struct object_list** process_blob (int /*<<< orphan*/ ,struct object_list**) ; 
 int /*<<< orphan*/  the_repository ; 
 scalar_t__ tree_entry (struct tree_desc*,struct name_entry*) ; 

__attribute__((used)) static struct object_list **process_tree(struct tree *tree,
					 struct object_list **p)
{
	struct object *obj = &tree->object;
	struct tree_desc desc;
	struct name_entry entry;

	obj->flags |= LOCAL;

	if (obj->flags & (UNINTERESTING | SEEN))
		return p;
	if (parse_tree(tree) < 0)
		die("bad tree object %s", oid_to_hex(&obj->oid));

	obj->flags |= SEEN;
	p = add_one_object(obj, p);

	init_tree_desc(&desc, tree->buffer, tree->size);

	while (tree_entry(&desc, &entry))
		switch (object_type(entry.mode)) {
		case OBJ_TREE:
			p = process_tree(lookup_tree(the_repository, &entry.oid),
					 p);
			break;
		case OBJ_BLOB:
			p = process_blob(lookup_blob(the_repository, &entry.oid),
					 p);
			break;
		default:
			/* Subproject commit - not in this repository */
			break;
		}

	free_tree_buffer(tree);
	return p;
}