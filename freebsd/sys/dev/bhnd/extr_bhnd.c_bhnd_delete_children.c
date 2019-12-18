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
struct bhnd_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_DEVICE_ORDER_DETACH ; 
 int /*<<< orphan*/  bhnd_bus_free_children (int /*<<< orphan*/ *) ; 
 int bhnd_bus_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ) ; 
 int device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_delete_children(struct bhnd_softc *sc)
{
	device_t		*devs;
	int			 ndevs;
	int			 error;

	/* Fetch children in detach order */
	error = bhnd_bus_get_children(sc->dev, &devs, &ndevs,
	    BHND_DEVICE_ORDER_DETACH);
	if (error)
		return (error);

	/* Perform detach */
	for (int i = 0; i < ndevs; i++) {
		device_t child = devs[i];

		/* Terminate on first error */
		if ((error = device_delete_child(sc->dev, child)))
			goto cleanup;
	}

cleanup:
	bhnd_bus_free_children(devs);
	return (error);
}