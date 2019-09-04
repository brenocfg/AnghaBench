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
struct object_array_entry {int /*<<< orphan*/  name; } ;
struct object_array {unsigned int nr; struct object_array_entry* objects; } ;

/* Variables and functions */
 int /*<<< orphan*/  contains_name (struct object_array*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_array_release_entry (struct object_array_entry*) ; 

void object_array_remove_duplicates(struct object_array *array)
{
	unsigned nr = array->nr, src;
	struct object_array_entry *objects = array->objects;

	array->nr = 0;
	for (src = 0; src < nr; src++) {
		if (!contains_name(array, objects[src].name)) {
			if (src != array->nr)
				objects[array->nr] = objects[src];
			array->nr++;
		} else {
			object_array_release_entry(&objects[src]);
		}
	}
}