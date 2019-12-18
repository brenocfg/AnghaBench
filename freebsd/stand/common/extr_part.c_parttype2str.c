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
typedef  enum partition_type { ____Placeholder_partition_type } partition_type ;
struct TYPE_3__ {int type; char const* desc; } ;

/* Variables and functions */
 size_t nitems (TYPE_1__*) ; 
 TYPE_1__* ptypes ; 

const char *
parttype2str(enum partition_type type)
{
	size_t i;

	for (i = 0; i < nitems(ptypes); i++)
		if (ptypes[i].type == type)
			return (ptypes[i].desc);
	return (ptypes[0].desc);
}