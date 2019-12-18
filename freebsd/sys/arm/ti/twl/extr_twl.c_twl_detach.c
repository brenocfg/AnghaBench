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
struct twl_softc {scalar_t__ sc_clks; scalar_t__ sc_vreg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  TWL_LOCK_DESTROY (struct twl_softc*) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct twl_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
twl_detach(device_t dev)
{
	struct twl_softc *sc;

	sc = device_get_softc(dev);

	if (sc->sc_vreg)
		device_delete_child(dev, sc->sc_vreg);
	if (sc->sc_clks)
		device_delete_child(dev, sc->sc_clks);
	

	TWL_LOCK_DESTROY(sc);

	return (0);
}