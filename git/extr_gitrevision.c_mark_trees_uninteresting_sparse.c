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
struct TYPE_2__ {int flags; } ;
struct tree {TYPE_1__ object; } ;
struct repository {int dummy; } ;
struct oidset {int dummy; } ;
struct path_and_oids_entry {struct oidset trees; } ;
struct oidset_iter {int dummy; } ;
struct object_id {int dummy; } ;
struct hashmap_iter {int dummy; } ;
struct hashmap {int dummy; } ;

/* Variables and functions */
 int UNINTERESTING ; 
 int /*<<< orphan*/  add_children_by_path (struct repository*,struct tree*,struct hashmap*) ; 
 int /*<<< orphan*/  hashmap_iter_init (struct hashmap*,struct hashmap_iter*) ; 
 struct path_and_oids_entry* hashmap_iter_next (struct hashmap_iter*) ; 
 struct tree* lookup_tree (struct repository*,struct object_id*) ; 
 int /*<<< orphan*/  oidset_iter_init (struct oidset*,struct oidset_iter*) ; 
 struct object_id* oidset_iter_next (struct oidset_iter*) ; 
 int /*<<< orphan*/  paths_and_oids_clear (struct hashmap*) ; 
 int /*<<< orphan*/  paths_and_oids_init (struct hashmap*) ; 

void mark_trees_uninteresting_sparse(struct repository *r,
				     struct oidset *trees)
{
	unsigned has_interesting = 0, has_uninteresting = 0;
	struct hashmap map;
	struct hashmap_iter map_iter;
	struct path_and_oids_entry *entry;
	struct object_id *oid;
	struct oidset_iter iter;

	oidset_iter_init(trees, &iter);
	while ((!has_interesting || !has_uninteresting) &&
	       (oid = oidset_iter_next(&iter))) {
		struct tree *tree = lookup_tree(r, oid);

		if (!tree)
			continue;

		if (tree->object.flags & UNINTERESTING)
			has_uninteresting = 1;
		else
			has_interesting = 1;
	}

	/* Do not walk unless we have both types of trees. */
	if (!has_uninteresting || !has_interesting)
		return;

	paths_and_oids_init(&map);

	oidset_iter_init(trees, &iter);
	while ((oid = oidset_iter_next(&iter))) {
		struct tree *tree = lookup_tree(r, oid);
		add_children_by_path(r, tree, &map);
	}

	hashmap_iter_init(&map, &map_iter);
	while ((entry = hashmap_iter_next(&map_iter)))
		mark_trees_uninteresting_sparse(r, &entry->trees);

	paths_and_oids_clear(&map);
}