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
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ bhnd_devclass ; 
 scalar_t__ devclass_find (char*) ; 
 scalar_t__ device_get_devclass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 

device_t
bhnd_find_bridge_root(device_t dev, devclass_t bus_class)
{
	devclass_t	bhndb_class;
	device_t	parent;

	KASSERT(device_get_devclass(device_get_parent(dev)) == bhnd_devclass,
	   ("%s not a bhnd device", device_get_nameunit(dev)));

	bhndb_class = devclass_find("bhndb");

	/* Walk the device tree until we hit a bridge */
	parent = dev;
	while ((parent = device_get_parent(parent)) != NULL) {
		if (device_get_devclass(parent) == bhndb_class)
			break;
	}

	/* No bridge? */
	if (parent == NULL)
		return (NULL);

	/* Search for a parent attached to the expected bus class */
	while ((parent = device_get_parent(parent)) != NULL) {
		device_t bus;

		bus = device_get_parent(parent);
		if (bus != NULL && device_get_devclass(bus) == bus_class)
			return (parent);
	}

	/* Not found */
	return (NULL);
}