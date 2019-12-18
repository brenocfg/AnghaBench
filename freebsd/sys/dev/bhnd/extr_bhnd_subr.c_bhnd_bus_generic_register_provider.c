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
typedef  int /*<<< orphan*/  bhnd_service_t ;

/* Variables and functions */
 int BHND_BUS_REGISTER_PROVIDER (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 

int
bhnd_bus_generic_register_provider(device_t dev, device_t child,
    device_t provider, bhnd_service_t service)
{
	device_t parent = device_get_parent(dev);

	if (parent != NULL) {
		return (BHND_BUS_REGISTER_PROVIDER(parent, child,
		    provider, service));
	}

	return (ENXIO);
}