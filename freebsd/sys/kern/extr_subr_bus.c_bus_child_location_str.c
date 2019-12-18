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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int BUS_CHILD_LOCATION_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 

int
bus_child_location_str(device_t child, char *buf, size_t buflen)
{
	device_t parent;

	parent = device_get_parent(child);
	if (parent == NULL) {
		*buf = '\0';
		return (0);
	}
	return (BUS_CHILD_LOCATION_STR(parent, child, buf, buflen));
}