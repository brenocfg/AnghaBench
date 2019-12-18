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
struct object_entry {int dummy; } ;
struct object {int /*<<< orphan*/  oid; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJECT_ADDED ; 
 int /*<<< orphan*/  add_object_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_preferred_base_object (char const*) ; 
 int /*<<< orphan*/  oe_set_tree_depth (int /*<<< orphan*/ *,struct object_entry*,unsigned int) ; 
 unsigned int oe_tree_depth (int /*<<< orphan*/ *,struct object_entry*) ; 
 struct object_entry* packlist_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  to_pack ; 
 scalar_t__ use_delta_islands ; 

__attribute__((used)) static void show_object(struct object *obj, const char *name, void *data)
{
	add_preferred_base_object(name);
	add_object_entry(&obj->oid, obj->type, name, 0);
	obj->flags |= OBJECT_ADDED;

	if (use_delta_islands) {
		const char *p;
		unsigned depth;
		struct object_entry *ent;

		/* the empty string is a root tree, which is depth 0 */
		depth = *name ? 1 : 0;
		for (p = strchr(name, '/'); p; p = strchr(p + 1, '/'))
			depth++;

		ent = packlist_find(&to_pack, &obj->oid);
		if (ent && depth > oe_tree_depth(&to_pack, ent))
			oe_set_tree_depth(&to_pack, ent, depth);
	}
}