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
struct object {int flags; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_OBJECT ; 
 int HAS_OBJ ; 
 int REACHABLE ; 
 int SEEN ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errors_found ; 
 int fsck_obj (struct object*,void*,unsigned long) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 struct object* parse_object_buffer (int /*<<< orphan*/ ,struct object_id const*,int,unsigned long,void*,int*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int fsck_obj_buffer(const struct object_id *oid, enum object_type type,
			   unsigned long size, void *buffer, int *eaten)
{
	/*
	 * Note, buffer may be NULL if type is OBJ_BLOB. See
	 * verify_packfile(), data_valid variable for details.
	 */
	struct object *obj;
	obj = parse_object_buffer(the_repository, oid, type, size, buffer,
				  eaten);
	if (!obj) {
		errors_found |= ERROR_OBJECT;
		return error(_("%s: object corrupt or missing"),
			     oid_to_hex(oid));
	}
	obj->flags &= ~(REACHABLE | SEEN);
	obj->flags |= HAS_OBJ;
	return fsck_obj(obj, buffer, size);
}