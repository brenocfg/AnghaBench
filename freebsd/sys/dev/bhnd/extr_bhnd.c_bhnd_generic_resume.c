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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_DEVICE_ORDER_ATTACH ; 
 int BUS_RESUME_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  bhnd_bus_free_children (int /*<<< orphan*/ *) ; 
 int bhnd_bus_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_is_attached (int /*<<< orphan*/ ) ; 

int
bhnd_generic_resume(device_t dev)
{
	device_t	*devs;
	int		 ndevs;
	int		 error;

	if (!device_is_attached(dev))
		return (EBUSY);

	/* Fetch children in attach order */
	error = bhnd_bus_get_children(dev, &devs, &ndevs,
	    BHND_DEVICE_ORDER_ATTACH);
	if (error)
		return (error);

	/* Perform resume */
	for (int i = 0; i < ndevs; i++) {
		device_t child = devs[i];

		/* Terminate on first error */
		if ((error = BUS_RESUME_CHILD(device_get_parent(child), child)))
			goto cleanup;
	}

cleanup:
	bhnd_bus_free_children(devs);
	return (error);
}