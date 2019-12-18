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
struct chipc_softc {int /*<<< orphan*/  core_region; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_SERVICE_ANY ; 
 int /*<<< orphan*/  CHIPC_LOCK_DESTROY (struct chipc_softc*) ; 
 int RF_ACTIVE ; 
 int RF_ALLOCATED ; 
 int bhnd_deregister_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipc_free_rman (struct chipc_softc*) ; 
 int /*<<< orphan*/  chipc_release_region (struct chipc_softc*,int /*<<< orphan*/ ,int) ; 
 int device_delete_children (int /*<<< orphan*/ ) ; 
 struct chipc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
chipc_detach(device_t dev)
{
	struct chipc_softc	*sc;
	int			 error;

	sc = device_get_softc(dev);

	if ((error = bus_generic_detach(dev)))
		return (error);

	if ((error = device_delete_children(dev)))
		return (error);

	if ((error = bhnd_deregister_provider(dev, BHND_SERVICE_ANY)))
		return (error);

	chipc_release_region(sc, sc->core_region, RF_ALLOCATED|RF_ACTIVE);
	chipc_free_rman(sc);

	CHIPC_LOCK_DESTROY(sc);

	return (0);
}