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
struct object {scalar_t__ type; int /*<<< orphan*/  oid; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 scalar_t__ OBJ_NONE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  object_as_type (int /*<<< orphan*/ ,struct object*,int,int /*<<< orphan*/ ) ; 
 int oid_object_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 
 char* type_name (scalar_t__) ; 

__attribute__((used)) static const char *printable_type(struct object *obj)
{
	const char *ret;

	if (obj->type == OBJ_NONE) {
		enum object_type type = oid_object_info(the_repository,
							&obj->oid, NULL);
		if (type > 0)
			object_as_type(the_repository, obj, type, 0);
	}

	ret = type_name(obj->type);
	if (!ret)
		ret = _("unknown");

	return ret;
}