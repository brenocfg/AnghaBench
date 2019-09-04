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
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int contains_name(struct object_array *array, const char *name)
{
	unsigned nr = array->nr, i;
	struct object_array_entry *object = array->objects;

	for (i = 0; i < nr; i++, object++)
		if (!strcmp(object->name, name))
			return 1;
	return 0;
}