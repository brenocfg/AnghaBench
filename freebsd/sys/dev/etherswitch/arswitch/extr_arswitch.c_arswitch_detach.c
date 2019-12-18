#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  entries; } ;
struct arswitch_softc {int numphys; int /*<<< orphan*/  sc_mtx; TYPE_1__ atu; int /*<<< orphan*/ * ifname; int /*<<< orphan*/ ** ifp; int /*<<< orphan*/ ** miibus; int /*<<< orphan*/  callout_tick; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct arswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
arswitch_detach(device_t dev)
{
	struct arswitch_softc *sc = device_get_softc(dev);
	int i;

	callout_drain(&sc->callout_tick);

	for (i=0; i < sc->numphys; i++) {
		if (sc->miibus[i] != NULL)
			device_delete_child(dev, sc->miibus[i]);
		if (sc->ifp[i] != NULL)
			if_free(sc->ifp[i]);
		free(sc->ifname[i], M_DEVBUF);
	}

	free(sc->atu.entries, M_DEVBUF);

	bus_generic_detach(dev);
	mtx_destroy(&sc->sc_mtx);

	return (0);
}