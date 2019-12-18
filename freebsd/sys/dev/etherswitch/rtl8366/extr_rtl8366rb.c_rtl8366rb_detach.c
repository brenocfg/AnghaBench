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
struct rtl8366rb_softc {int numphys; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  callout_mtx; int /*<<< orphan*/  callout_tick; int /*<<< orphan*/ * ifname; int /*<<< orphan*/ ** ifp; scalar_t__* miibus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct rtl8366rb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rtl8366rb_detach(device_t dev)
{
	struct rtl8366rb_softc *sc;
	int i;

	sc = device_get_softc(dev);

	for (i=0; i < sc->numphys; i++) {
		if (sc->miibus[i])
			device_delete_child(dev, sc->miibus[i]);
		if (sc->ifp[i] != NULL)
			if_free(sc->ifp[i]);
		free(sc->ifname[i], M_DEVBUF);
	}
	bus_generic_detach(dev);
	callout_drain(&sc->callout_tick);
	mtx_destroy(&sc->callout_mtx);
	mtx_destroy(&sc->sc_mtx);

	return (0);
}