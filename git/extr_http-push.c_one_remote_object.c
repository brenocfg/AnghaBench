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
struct object_id {int dummy; } ;
struct object {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  REMOTE ; 
 struct object* lookup_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  object_list_contains (int /*<<< orphan*/ ,struct object*) ; 
 int /*<<< orphan*/  object_list_insert (struct object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  objects ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void one_remote_object(const struct object_id *oid)
{
	struct object *obj;

	obj = lookup_object(the_repository, oid);
	if (!obj)
		obj = parse_object(the_repository, oid);

	/* Ignore remote objects that don't exist locally */
	if (!obj)
		return;

	obj->flags |= REMOTE;
	if (!object_list_contains(objects, obj))
		object_list_insert(obj, &objects);
}