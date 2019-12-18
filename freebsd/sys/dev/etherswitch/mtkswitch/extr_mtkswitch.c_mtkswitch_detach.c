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
struct mtkswitch_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * ifname; int /*<<< orphan*/ ** ifp; int /*<<< orphan*/ ** miibus; int /*<<< orphan*/  callout_tick; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MTKSWITCH_MAX_PHYS ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mtkswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mtkswitch_detach(device_t dev)
{
	struct mtkswitch_softc *sc = device_get_softc(dev);
	int phy;

	callout_drain(&sc->callout_tick);

	for (phy = 0; phy < MTKSWITCH_MAX_PHYS; phy++) {
		if (sc->miibus[phy] != NULL)
			device_delete_child(dev, sc->miibus[phy]);
		if (sc->ifp[phy] != NULL)
			if_free(sc->ifp[phy]);
		free(sc->ifname[phy], M_DEVBUF);
	}

	bus_generic_detach(dev);
	mtx_destroy(&sc->sc_mtx);

	return (0);
}