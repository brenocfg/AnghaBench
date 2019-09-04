#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct object {unsigned int flags; } ;
struct TYPE_4__ {TYPE_1__* parsed_objects; } ;
struct TYPE_3__ {int obj_hash_size; struct object** obj_hash; } ;

/* Variables and functions */
 TYPE_2__* the_repository ; 

void clear_object_flags(unsigned flags)
{
	int i;

	for (i=0; i < the_repository->parsed_objects->obj_hash_size; i++) {
		struct object *obj = the_repository->parsed_objects->obj_hash[i];
		if (obj)
			obj->flags &= ~flags;
	}
}