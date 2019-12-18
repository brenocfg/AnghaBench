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
struct object {int /*<<< orphan*/  type; } ;
struct obj_buffer {int /*<<< orphan*/  size; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 struct object* lookup_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 struct obj_buffer* lookup_object_buffer (struct object*) ; 
 int /*<<< orphan*/  resolve_delta (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned long) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int resolve_against_held(unsigned nr, const struct object_id *base,
				void *delta_data, unsigned long delta_size)
{
	struct object *obj;
	struct obj_buffer *obj_buffer;
	obj = lookup_object(the_repository, base);
	if (!obj)
		return 0;
	obj_buffer = lookup_object_buffer(obj);
	if (!obj_buffer)
		return 0;
	resolve_delta(nr, obj->type, obj_buffer->buffer,
		      obj_buffer->size, delta_data, delta_size);
	return 1;
}