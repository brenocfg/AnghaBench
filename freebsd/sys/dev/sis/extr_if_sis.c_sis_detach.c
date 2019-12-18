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
struct sis_softc {int /*<<< orphan*/  sis_mtx; int /*<<< orphan*/ * sis_res; scalar_t__ sis_intrhand; scalar_t__ sis_miibus; int /*<<< orphan*/  sis_stat_ch; struct ifnet* sis_ifp; } ;
struct ifnet {int if_capenable; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SIS_LOCK (struct sis_softc*) ; 
 int /*<<< orphan*/  SIS_UNLOCK (struct sis_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct sis_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  ether_poll_deregister (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sis_dma_free (struct sis_softc*) ; 
 int /*<<< orphan*/  sis_res_spec ; 
 int /*<<< orphan*/  sis_stop (struct sis_softc*) ; 

__attribute__((used)) static int
sis_detach(device_t dev)
{
	struct sis_softc	*sc;
	struct ifnet		*ifp;

	sc = device_get_softc(dev);
	KASSERT(mtx_initialized(&sc->sis_mtx), ("sis mutex not initialized"));
	ifp = sc->sis_ifp;

#ifdef DEVICE_POLLING
	if (ifp->if_capenable & IFCAP_POLLING)
		ether_poll_deregister(ifp);
#endif

	/* These should only be active if attach succeeded. */
	if (device_is_attached(dev)) {
		SIS_LOCK(sc);
		sis_stop(sc);
		SIS_UNLOCK(sc);
		callout_drain(&sc->sis_stat_ch);
		ether_ifdetach(ifp);
	}
	if (sc->sis_miibus)
		device_delete_child(dev, sc->sis_miibus);
	bus_generic_detach(dev);

	if (sc->sis_intrhand)
		bus_teardown_intr(dev, sc->sis_res[1], sc->sis_intrhand);
	bus_release_resources(dev, sis_res_spec, sc->sis_res);

	if (ifp)
		if_free(ifp);

	sis_dma_free(sc);

	mtx_destroy(&sc->sis_mtx);

	return (0);
}