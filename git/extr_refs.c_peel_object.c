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
struct object {scalar_t__ type; int /*<<< orphan*/  oid; } ;
typedef  enum peel_status { ____Placeholder_peel_status } peel_status ;

/* Variables and functions */
 scalar_t__ OBJ_NONE ; 
 scalar_t__ OBJ_TAG ; 
 int PEEL_INVALID ; 
 int PEEL_NON_TAG ; 
 int PEEL_PEELED ; 
 struct object* deref_tag_noverify (struct object*) ; 
 struct object* lookup_unknown_object (struct object_id const*) ; 
 int /*<<< orphan*/  object_as_type (int /*<<< orphan*/ ,struct object*,int,int /*<<< orphan*/ ) ; 
 int oid_object_info (int /*<<< orphan*/ ,struct object_id const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 

enum peel_status peel_object(const struct object_id *name, struct object_id *oid)
{
	struct object *o = lookup_unknown_object(name);

	if (o->type == OBJ_NONE) {
		int type = oid_object_info(the_repository, name, NULL);
		if (type < 0 || !object_as_type(the_repository, o, type, 0))
			return PEEL_INVALID;
	}

	if (o->type != OBJ_TAG)
		return PEEL_NON_TAG;

	o = deref_tag_noverify(o);
	if (!o)
		return PEEL_INVALID;

	oidcpy(oid, &o->oid);
	return PEEL_PEELED;
}