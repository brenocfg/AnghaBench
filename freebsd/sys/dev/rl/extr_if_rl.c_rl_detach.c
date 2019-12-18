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
struct rl_softc {int suspended; int /*<<< orphan*/  rl_mtx; scalar_t__ rl_res; int /*<<< orphan*/  rl_res_id; int /*<<< orphan*/  rl_res_type; scalar_t__* rl_irq; scalar_t__* rl_intrhand; scalar_t__ rl_miibus; int /*<<< orphan*/  rl_stat_callout; struct ifnet* rl_ifp; } ;
struct ifnet {int if_capenable; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RL_LOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_UNLOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct rl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  ether_poll_deregister (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rl_dma_free (struct rl_softc*) ; 
 int /*<<< orphan*/  rl_stop (struct rl_softc*) ; 

__attribute__((used)) static int
rl_detach(device_t dev)
{
	struct rl_softc		*sc;
	struct ifnet		*ifp;

	sc = device_get_softc(dev);
	ifp = sc->rl_ifp;

	KASSERT(mtx_initialized(&sc->rl_mtx), ("rl mutex not initialized"));

#ifdef DEVICE_POLLING
	if (ifp->if_capenable & IFCAP_POLLING)
		ether_poll_deregister(ifp);
#endif
	/* These should only be active if attach succeeded */
	if (device_is_attached(dev)) {
		RL_LOCK(sc);
		rl_stop(sc);
		RL_UNLOCK(sc);
		callout_drain(&sc->rl_stat_callout);
		ether_ifdetach(ifp);
	}
#if 0
	sc->suspended = 1;
#endif
	if (sc->rl_miibus)
		device_delete_child(dev, sc->rl_miibus);
	bus_generic_detach(dev);

	if (sc->rl_intrhand[0])
		bus_teardown_intr(dev, sc->rl_irq[0], sc->rl_intrhand[0]);
	if (sc->rl_irq[0])
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->rl_irq[0]);
	if (sc->rl_res)
		bus_release_resource(dev, sc->rl_res_type, sc->rl_res_id,
		    sc->rl_res);

	if (ifp)
		if_free(ifp);

	rl_dma_free(sc);

	mtx_destroy(&sc->rl_mtx);

	return (0);
}