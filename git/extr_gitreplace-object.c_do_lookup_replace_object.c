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
struct repository {TYPE_1__* objects; } ;
struct object_id {int dummy; } ;
struct replace_object {struct object_id replacement; } ;
struct TYPE_2__ {int /*<<< orphan*/  replace_map; } ;

/* Variables and functions */
 int MAXREPLACEDEPTH ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 struct replace_object* oidmap_get (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  prepare_replace_object (struct repository*) ; 

const struct object_id *do_lookup_replace_object(struct repository *r,
						 const struct object_id *oid)
{
	int depth = MAXREPLACEDEPTH;
	const struct object_id *cur = oid;

	prepare_replace_object(r);

	/* Try to recursively replace the object */
	while (depth-- > 0) {
		struct replace_object *repl_obj =
			oidmap_get(r->objects->replace_map, cur);
		if (!repl_obj)
			return cur;
		cur = &repl_obj->replacement;
	}
	die(_("replace depth too high for object %s"), oid_to_hex(oid));
}