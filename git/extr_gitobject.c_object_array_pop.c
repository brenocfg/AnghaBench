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
struct object_array {int nr; TYPE_1__* objects; } ;
struct object {int dummy; } ;
struct TYPE_2__ {struct object* item; } ;

/* Variables and functions */
 int /*<<< orphan*/  object_array_release_entry (TYPE_1__*) ; 

struct object *object_array_pop(struct object_array *array)
{
	struct object *ret;

	if (!array->nr)
		return NULL;

	ret = array->objects[array->nr - 1].item;
	object_array_release_entry(&array->objects[array->nr - 1]);
	array->nr--;
	return ret;
}