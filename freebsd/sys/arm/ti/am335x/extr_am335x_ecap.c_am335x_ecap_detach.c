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
struct am335x_ecap_softc {scalar_t__ sc_mem_res; int /*<<< orphan*/  sc_mem_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PWM_LOCK (struct am335x_ecap_softc*) ; 
 int /*<<< orphan*/  PWM_LOCK_DESTROY (struct am335x_ecap_softc*) ; 
 int /*<<< orphan*/  PWM_UNLOCK (struct am335x_ecap_softc*) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct am335x_ecap_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
am335x_ecap_detach(device_t dev)
{
	struct am335x_ecap_softc *sc;

	sc = device_get_softc(dev);

	PWM_LOCK(sc);
	if (sc->sc_mem_res)
		bus_release_resource(dev, SYS_RES_MEMORY,
		    sc->sc_mem_rid, sc->sc_mem_res);
	PWM_UNLOCK(sc);

	PWM_LOCK_DESTROY(sc);


	return (0);
}