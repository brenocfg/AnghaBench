#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* s; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ value; } ;
typedef  TYPE_2__ attr_val ;

/* Variables and functions */
 scalar_t__ T_String ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void
destroy_attr_val(
	attr_val *	av
	)
{
	if (av) {
		if (T_String == av->type)
			free(av->value.s);
		free(av);
	}
}