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
struct tag {TYPE_1__* tagged; } ;
struct oid_array {int dummy; } ;
struct object_id {int dummy; } ;
struct object {scalar_t__ type; } ;
struct TYPE_2__ {struct object_id oid; } ;

/* Variables and functions */
 scalar_t__ OBJ_TAG ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ oid_array_lookup (struct oid_array*,struct object_id const*) ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static const struct object_id *match_points_at(struct oid_array *points_at,
					       const struct object_id *oid,
					       const char *refname)
{
	const struct object_id *tagged_oid = NULL;
	struct object *obj;

	if (oid_array_lookup(points_at, oid) >= 0)
		return oid;
	obj = parse_object(the_repository, oid);
	if (!obj)
		die(_("malformed object at '%s'"), refname);
	if (obj->type == OBJ_TAG)
		tagged_oid = &((struct tag *)obj)->tagged->oid;
	if (tagged_oid && oid_array_lookup(points_at, tagged_oid) >= 0)
		return tagged_oid;
	return NULL;
}