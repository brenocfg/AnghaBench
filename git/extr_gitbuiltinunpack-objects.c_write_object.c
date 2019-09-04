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
struct object {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct blob {TYPE_1__ object; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_4__ {struct object* obj; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_OPEN ; 
 int /*<<< orphan*/  FLAG_WRITTEN ; 
 int OBJ_BLOB ; 
 int /*<<< orphan*/  add_object_buffer (struct object*,void*,unsigned long) ; 
 int /*<<< orphan*/  added_object (unsigned int,int,void*,unsigned long) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  hash_object_file (void*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct blob* lookup_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* obj_list ; 
 struct object* parse_object_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,unsigned long,void*,int*) ; 
 int /*<<< orphan*/  strict ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  type_name (int) ; 
 scalar_t__ write_object_file (void*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void write_object(unsigned nr, enum object_type type,
			 void *buf, unsigned long size)
{
	if (!strict) {
		if (write_object_file(buf, size, type_name(type),
				      &obj_list[nr].oid) < 0)
			die("failed to write object");
		added_object(nr, type, buf, size);
		free(buf);
		obj_list[nr].obj = NULL;
	} else if (type == OBJ_BLOB) {
		struct blob *blob;
		if (write_object_file(buf, size, type_name(type),
				      &obj_list[nr].oid) < 0)
			die("failed to write object");
		added_object(nr, type, buf, size);
		free(buf);

		blob = lookup_blob(the_repository, &obj_list[nr].oid);
		if (blob)
			blob->object.flags |= FLAG_WRITTEN;
		else
			die("invalid blob object");
		obj_list[nr].obj = NULL;
	} else {
		struct object *obj;
		int eaten;
		hash_object_file(buf, size, type_name(type), &obj_list[nr].oid);
		added_object(nr, type, buf, size);
		obj = parse_object_buffer(the_repository, &obj_list[nr].oid,
					  type, size, buf,
					  &eaten);
		if (!obj)
			die("invalid %s", type_name(type));
		add_object_buffer(obj, buf, size);
		obj->flags |= FLAG_OPEN;
		obj_list[nr].obj = obj;
	}
}