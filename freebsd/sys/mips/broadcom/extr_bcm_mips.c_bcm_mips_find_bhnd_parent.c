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
typedef  scalar_t__ devclass_t ;

/* Variables and functions */
 scalar_t__ devclass_find (char*) ; 
 scalar_t__ device_get_devclass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 

__attribute__((used)) static device_t
bcm_mips_find_bhnd_parent(device_t dev)
{
	device_t	core, bus;
	devclass_t	bhnd_class;

	bhnd_class = devclass_find("bhnd");
	core = dev;
	while ((bus = device_get_parent(core)) != NULL) {
		if (device_get_devclass(bus) == bhnd_class)
			return (core);

		core = bus;
	}

	/* Not found */
	return (NULL);
}