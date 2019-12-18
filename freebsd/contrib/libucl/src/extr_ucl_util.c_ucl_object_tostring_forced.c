#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ ucl_object_t ;

/* Variables and functions */
 int UCL_OBJECT_BINARY ; 
 char const* ucl_copy_value_trash (TYPE_1__ const*) ; 

const char *
ucl_object_tostring_forced (const ucl_object_t *obj)
{
	/* TODO: For binary strings we might encode string here */
	if (!(obj->flags & UCL_OBJECT_BINARY)) {
		return ucl_copy_value_trash (obj);
	}

	return NULL;
}