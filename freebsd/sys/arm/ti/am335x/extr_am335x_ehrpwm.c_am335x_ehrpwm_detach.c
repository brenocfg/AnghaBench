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
struct am335x_ehrpwm_softc {scalar_t__ sc_mem_res; int /*<<< orphan*/  sc_mem_rid; int /*<<< orphan*/ * sc_busdev; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PWM_LOCK (struct am335x_ehrpwm_softc*) ; 
 int /*<<< orphan*/  PWM_LOCK_DESTROY (struct am335x_ehrpwm_softc*) ; 
 int /*<<< orphan*/  PWM_UNLOCK (struct am335x_ehrpwm_softc*) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct am335x_ehrpwm_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
am335x_ehrpwm_detach(device_t dev)
{
	struct am335x_ehrpwm_softc *sc;
	int error;

	sc = device_get_softc(dev);

	if ((error = bus_generic_detach(sc->sc_dev)) != 0)
		return (error);

	PWM_LOCK(sc);

	if (sc->sc_busdev != NULL)
		device_delete_child(dev, sc->sc_busdev);

	if (sc->sc_mem_res)
		bus_release_resource(dev, SYS_RES_MEMORY,
		    sc->sc_mem_rid, sc->sc_mem_res);

	PWM_UNLOCK(sc);

	PWM_LOCK_DESTROY(sc);

	return (0);
}