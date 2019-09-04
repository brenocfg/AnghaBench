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
struct tree_desc {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct tree {unsigned long size; TYPE_1__ object; void* buffer; } ;
struct object_id {int dummy; } ;
struct name_entry {struct object_id oid; int /*<<< orphan*/  mode; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int INCOMPLETE ; 
 int SEEN ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_tree_buffer (struct tree*) ; 
 int /*<<< orphan*/  has_object_file (struct object_id*) ; 
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,void*,unsigned long) ; 
 struct tree* lookup_tree (int /*<<< orphan*/ ,struct object_id const*) ; 
 void* read_object_file (struct object_id const*,int*,unsigned long*) ; 
 int /*<<< orphan*/  the_repository ; 
 scalar_t__ tree_entry (struct tree_desc*,struct name_entry*) ; 

__attribute__((used)) static int tree_is_complete(const struct object_id *oid)
{
	struct tree_desc desc;
	struct name_entry entry;
	int complete;
	struct tree *tree;

	tree = lookup_tree(the_repository, oid);
	if (!tree)
		return 0;
	if (tree->object.flags & SEEN)
		return 1;
	if (tree->object.flags & INCOMPLETE)
		return 0;

	if (!tree->buffer) {
		enum object_type type;
		unsigned long size;
		void *data = read_object_file(oid, &type, &size);
		if (!data) {
			tree->object.flags |= INCOMPLETE;
			return 0;
		}
		tree->buffer = data;
		tree->size = size;
	}
	init_tree_desc(&desc, tree->buffer, tree->size);
	complete = 1;
	while (tree_entry(&desc, &entry)) {
		if (!has_object_file(&entry.oid) ||
		    (S_ISDIR(entry.mode) && !tree_is_complete(&entry.oid))) {
			tree->object.flags |= INCOMPLETE;
			complete = 0;
		}
	}
	free_tree_buffer(tree);

	if (complete)
		tree->object.flags |= SEEN;
	return complete;
}