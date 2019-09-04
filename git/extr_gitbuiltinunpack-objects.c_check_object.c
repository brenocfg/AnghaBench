#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct object {int flags; int type; int /*<<< orphan*/  oid; } ;
struct obj_buffer {int /*<<< orphan*/  size; int /*<<< orphan*/  buffer; } ;
struct fsck_options {int dummy; } ;
struct TYPE_4__ {int (* walk ) (struct object*,int,void*,struct fsck_options*) ;} ;

/* Variables and functions */
 int FLAG_OPEN ; 
 int FLAG_WRITTEN ; 
 int OBJ_ANY ; 
 int /*<<< orphan*/  die (char*,...) ; 
 scalar_t__ fsck_object (struct object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ fsck_options ; 
 scalar_t__ fsck_walk (struct object*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct obj_buffer* lookup_object_buffer (struct object*) ; 
 int oid_object_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  write_cached_object (struct object*,struct obj_buffer*) ; 

__attribute__((used)) static int check_object(struct object *obj, int type, void *data, struct fsck_options *options)
{
	struct obj_buffer *obj_buf;

	if (!obj)
		return 1;

	if (obj->flags & FLAG_WRITTEN)
		return 0;

	if (type != OBJ_ANY && obj->type != type)
		die("object type mismatch");

	if (!(obj->flags & FLAG_OPEN)) {
		unsigned long size;
		int type = oid_object_info(the_repository, &obj->oid, &size);
		if (type != obj->type || type <= 0)
			die("object of unexpected type");
		obj->flags |= FLAG_WRITTEN;
		return 0;
	}

	obj_buf = lookup_object_buffer(obj);
	if (!obj_buf)
		die("Whoops! Cannot find object '%s'", oid_to_hex(&obj->oid));
	if (fsck_object(obj, obj_buf->buffer, obj_buf->size, &fsck_options))
		die("fsck error in packed object");
	fsck_options.walk = check_object;
	if (fsck_walk(obj, NULL, &fsck_options))
		die("Error on reachable objects of %s", oid_to_hex(&obj->oid));
	write_cached_object(obj, obj_buf);
	return 0;
}