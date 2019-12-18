#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* device_t ;
typedef  int /*<<< orphan*/  devclass_t ;
struct TYPE_5__ {struct TYPE_5__* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  devclass_find (char const*) ; 
 TYPE_1__* devclass_get_device (int /*<<< orphan*/ ,int) ; 
 int devclass_get_maxunit (int /*<<< orphan*/ ) ; 

device_t
device_find_child(device_t dev, const char *classname, int unit)
{
	devclass_t dc;
	device_t child;

	dc = devclass_find(classname);
	if (!dc)
		return (NULL);

	if (unit != -1) {
		child = devclass_get_device(dc, unit);
		if (child && child->parent == dev)
			return (child);
	} else {
		for (unit = 0; unit < devclass_get_maxunit(dc); unit++) {
			child = devclass_get_device(dc, unit);
			if (child && child->parent == dev)
				return (child);
		}
	}
	return (NULL);
}