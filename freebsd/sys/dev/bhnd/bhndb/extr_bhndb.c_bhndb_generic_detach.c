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
struct bhndb_softc {int /*<<< orphan*/  bus_res; int /*<<< orphan*/  services; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHNDB_LOCK_DESTROY (struct bhndb_softc*) ; 
 int bhnd_service_registry_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhndb_free_resources (int /*<<< orphan*/ ) ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int device_delete_children (int /*<<< orphan*/ ) ; 
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
bhndb_generic_detach(device_t dev)
{
	struct bhndb_softc	*sc;
	int			 error;

	sc = device_get_softc(dev);

	/* Detach children */
	if ((error = bus_generic_detach(dev)))
		return (error);

	/* Delete children */
	if ((error = device_delete_children(dev)))
		return (error);

	/* Clean up our service registry */
	if ((error = bhnd_service_registry_fini(&sc->services)))
		return (error);

	/* Clean up our driver state. */
	bhndb_free_resources(sc->bus_res);
	
	BHNDB_LOCK_DESTROY(sc);

	return (0);
}