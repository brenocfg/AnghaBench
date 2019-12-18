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
struct tag {TYPE_1__ object; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int OBJ_TAG ; 
 int error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int parse_tag_buffer (int /*<<< orphan*/ ,struct tag*,void*,unsigned long) ; 
 void* read_object_file (int /*<<< orphan*/ *,int*,unsigned long*) ; 
 int /*<<< orphan*/  the_repository ; 

int parse_tag(struct tag *item)
{
	enum object_type type;
	void *data;
	unsigned long size;
	int ret;

	if (item->object.parsed)
		return 0;
	data = read_object_file(&item->object.oid, &type, &size);
	if (!data)
		return error("Could not read %s",
			     oid_to_hex(&item->object.oid));
	if (type != OBJ_TAG) {
		free(data);
		return error("Object %s not a tag",
			     oid_to_hex(&item->object.oid));
	}
	ret = parse_tag_buffer(the_repository, item, data, size);
	free(data);
	return ret;
}