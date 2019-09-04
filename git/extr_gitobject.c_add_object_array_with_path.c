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
struct object_array_entry {unsigned int mode; int /*<<< orphan*/ * path; int /*<<< orphan*/ * name; struct object* item; } ;
struct object_array {unsigned int nr; unsigned int alloc; struct object_array_entry* objects; } ;
struct object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REALLOC_ARRAY (struct object_array_entry*,unsigned int) ; 
 int /*<<< orphan*/ * object_array_slopbuf ; 
 void* xstrdup (char const*) ; 

void add_object_array_with_path(struct object *obj, const char *name,
				struct object_array *array,
				unsigned mode, const char *path)
{
	unsigned nr = array->nr;
	unsigned alloc = array->alloc;
	struct object_array_entry *objects = array->objects;
	struct object_array_entry *entry;

	if (nr >= alloc) {
		alloc = (alloc + 32) * 2;
		REALLOC_ARRAY(objects, alloc);
		array->alloc = alloc;
		array->objects = objects;
	}
	entry = &objects[nr];
	entry->item = obj;
	if (!name)
		entry->name = NULL;
	else if (!*name)
		/* Use our own empty string instead of allocating one: */
		entry->name = object_array_slopbuf;
	else
		entry->name = xstrdup(name);
	entry->mode = mode;
	if (path)
		entry->path = xstrdup(path);
	else
		entry->path = NULL;
	array->nr = ++nr;
}