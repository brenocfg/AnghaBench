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
struct TYPE_3__ {int type; char const* name; } ;

/* Variables and functions */
 TYPE_1__* device_types ; 
 int nitems (TYPE_1__*) ; 

__attribute__((used)) static const char *
device_typename(int type)
{
	int i;

	for (i = 0; i < nitems(device_types); i++)
		if (device_types[i].type == type)
			return (device_types[i].name);

	return ("<unknown>");
}