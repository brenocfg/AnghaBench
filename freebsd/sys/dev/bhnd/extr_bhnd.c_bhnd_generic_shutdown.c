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
 int /*<<< orphan*/  BHND_DEVICE_ORDER_DETACH ; 
 int EBUSY ; 
 int /*<<< orphan*/  bhnd_bus_free_children (int /*<<< orphan*/ *) ; 
 int bhnd_bus_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_is_attached (int /*<<< orphan*/ ) ; 
 int device_shutdown (int /*<<< orphan*/ ) ; 

int
bhnd_generic_shutdown(device_t dev)
{
	device_t	*devs;
	int		 ndevs;
	int		 error;

	if (!device_is_attached(dev))
		return (EBUSY);

	/* Fetch children in detach order */
	error = bhnd_bus_get_children(dev, &devs, &ndevs,
	    BHND_DEVICE_ORDER_DETACH);
	if (error)
		return (error);

	/* Perform shutdown */
	for (int i = 0; i < ndevs; i++) {
		device_t child = devs[i];

		/* Terminate on first error */
		if ((error = device_shutdown(child)))
			goto cleanup;
	}

cleanup:
	bhnd_bus_free_children(devs);
	return (error);
}