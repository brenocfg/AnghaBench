#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ ucl_object_t ;

/* Variables and functions */
 int NBBY ; 
 int PRIOBITS ; 

void
ucl_object_set_priority (ucl_object_t *obj,
		unsigned int priority)
{
	if (obj != NULL) {
		priority &= (0x1 << PRIOBITS) - 1;
		priority <<= ((sizeof (obj->flags) * NBBY) - PRIOBITS);
		priority |= obj->flags & ((1 << ((sizeof (obj->flags) * NBBY) -
				PRIOBITS)) - 1);
		obj->flags = priority;
	}
}