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
struct object_array_entry {int dummy; } ;
struct object_array {unsigned int nr; struct object_array_entry* objects; } ;
typedef  scalar_t__ (* object_array_each_func_t ) (struct object_array_entry*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  object_array_release_entry (struct object_array_entry*) ; 

void object_array_filter(struct object_array *array,
			 object_array_each_func_t want, void *cb_data)
{
	unsigned nr = array->nr, src, dst;
	struct object_array_entry *objects = array->objects;

	for (src = dst = 0; src < nr; src++) {
		if (want(&objects[src], cb_data)) {
			if (src != dst)
				objects[dst] = objects[src];
			dst++;
		} else {
			object_array_release_entry(&objects[src]);
		}
	}
	array->nr = dst;
}