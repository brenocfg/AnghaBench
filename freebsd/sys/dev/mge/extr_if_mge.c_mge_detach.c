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
struct mge_softc {int mge_intr_cnt; int /*<<< orphan*/  transmit_lock; int /*<<< orphan*/  receive_lock; int /*<<< orphan*/ * res; scalar_t__ ifp; int /*<<< orphan*/ * ih_cookie; int /*<<< orphan*/  wd_callout; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  description; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct mge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (scalar_t__) ; 
 int /*<<< orphan*/  if_free (scalar_t__) ; 
 int /*<<< orphan*/  mge_free_dma (struct mge_softc*) ; 
 TYPE_1__* mge_intrs ; 
 int /*<<< orphan*/  mge_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  res_spec ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_smi ; 

__attribute__((used)) static int
mge_detach(device_t dev)
{
	struct mge_softc *sc;
	int error,i;

	sc = device_get_softc(dev);

	/* Stop controller and free TX queue */
	if (sc->ifp)
		mge_shutdown(dev);

	/* Wait for stopping ticks */
        callout_drain(&sc->wd_callout);

	/* Stop and release all interrupts */
	for (i = 0; i < sc->mge_intr_cnt; ++i) {
		if (!sc->ih_cookie[i])
			continue;

		error = bus_teardown_intr(dev, sc->res[1 + i],
		    sc->ih_cookie[i]);
		if (error)
			device_printf(dev, "could not release %s\n",
			    mge_intrs[(sc->mge_intr_cnt == 1 ? 0 : i + 1)].description);
	}

	/* Detach network interface */
	if (sc->ifp) {
		ether_ifdetach(sc->ifp);
		if_free(sc->ifp);
	}

	/* Free DMA resources */
	mge_free_dma(sc);

	/* Free IO memory handler */
	bus_release_resources(dev, res_spec, sc->res);

	/* Destroy mutexes */
	mtx_destroy(&sc->receive_lock);
	mtx_destroy(&sc->transmit_lock);

	if (device_get_unit(dev) == 0)
		sx_destroy(&sx_smi);

	return (0);
}