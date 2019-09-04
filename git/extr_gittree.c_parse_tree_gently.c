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
struct TYPE_2__ {int /*<<< orphan*/  oid; scalar_t__ parsed; } ;
struct tree {TYPE_1__ object; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int OBJ_TREE ; 
 int error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int parse_tree_buffer (struct tree*,void*,unsigned long) ; 
 void* read_object_file (int /*<<< orphan*/ *,int*,unsigned long*) ; 

int parse_tree_gently(struct tree *item, int quiet_on_missing)
{
	 enum object_type type;
	 void *buffer;
	 unsigned long size;

	if (item->object.parsed)
		return 0;
	buffer = read_object_file(&item->object.oid, &type, &size);
	if (!buffer)
		return quiet_on_missing ? -1 :
			error("Could not read %s",
			     oid_to_hex(&item->object.oid));
	if (type != OBJ_TREE) {
		free(buffer);
		return error("Object %s not a tree",
			     oid_to_hex(&item->object.oid));
	}
	return parse_tree_buffer(item, buffer, size);
}