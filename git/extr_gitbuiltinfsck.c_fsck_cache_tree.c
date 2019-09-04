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
struct object {scalar_t__ type; int /*<<< orphan*/  flags; } ;
struct cache_tree {scalar_t__ entry_count; int subtree_nr; TYPE_1__** down; int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {int /*<<< orphan*/  object_names; } ;
struct TYPE_3__ {struct cache_tree* cache_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_REFS ; 
 scalar_t__ OBJ_TREE ; 
 int /*<<< orphan*/  USED ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_decoration (int /*<<< orphan*/ ,struct object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errors_found ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ fsck_walk_options ; 
 int /*<<< orphan*/  mark_object_reachable (struct object*) ; 
 scalar_t__ name_objects ; 
 int objerror (struct object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 struct object* parse_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  the_repository ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static int fsck_cache_tree(struct cache_tree *it)
{
	int i;
	int err = 0;

	if (verbose)
		fprintf_ln(stderr, _("Checking cache tree"));

	if (0 <= it->entry_count) {
		struct object *obj = parse_object(the_repository, &it->oid);
		if (!obj) {
			error(_("%s: invalid sha1 pointer in cache-tree"),
			      oid_to_hex(&it->oid));
			errors_found |= ERROR_REFS;
			return 1;
		}
		obj->flags |= USED;
		if (name_objects)
			add_decoration(fsck_walk_options.object_names,
				obj, xstrdup(":"));
		mark_object_reachable(obj);
		if (obj->type != OBJ_TREE)
			err |= objerror(obj, _("non-tree in cache-tree"));
	}
	for (i = 0; i < it->subtree_nr; i++)
		err |= fsck_cache_tree(it->down[i]->cache_tree);
	return err;
}