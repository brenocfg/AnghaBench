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
struct object_array {int nr; int alloc; int /*<<< orphan*/ * objects; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  object_array_release_entry (int /*<<< orphan*/ *) ; 

void object_array_clear(struct object_array *array)
{
	int i;
	for (i = 0; i < array->nr; i++)
		object_array_release_entry(&array->objects[i]);
	FREE_AND_NULL(array->objects);
	array->nr = array->alloc = 0;
}