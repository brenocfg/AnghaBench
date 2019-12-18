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
struct fxp_softc {int /*<<< orphan*/ * ih; int /*<<< orphan*/ * fxp_res; int /*<<< orphan*/  dev; int /*<<< orphan*/  ifp; int /*<<< orphan*/  stat_ch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_1 (struct fxp_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FXP_CSR_SCB_INTRCNTL ; 
 int /*<<< orphan*/  FXP_LOCK (struct fxp_softc*) ; 
 int /*<<< orphan*/  FXP_SCB_INTR_DISABLE ; 
 int /*<<< orphan*/  FXP_UNLOCK (struct fxp_softc*) ; 
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct fxp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_poll_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fxp_release (struct fxp_softc*) ; 
 int /*<<< orphan*/  fxp_stop (struct fxp_softc*) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fxp_detach(device_t dev)
{
	struct fxp_softc *sc = device_get_softc(dev);

#ifdef DEVICE_POLLING
	if (if_getcapenable(sc->ifp) & IFCAP_POLLING)
		ether_poll_deregister(sc->ifp);
#endif

	FXP_LOCK(sc);
	/*
	 * Stop DMA and drop transmit queue, but disable interrupts first.
	 */
	CSR_WRITE_1(sc, FXP_CSR_SCB_INTRCNTL, FXP_SCB_INTR_DISABLE);
	fxp_stop(sc);
	FXP_UNLOCK(sc);
	callout_drain(&sc->stat_ch);

	/*
	 * Close down routes etc.
	 */
	ether_ifdetach(sc->ifp);

	/*
	 * Unhook interrupt before dropping lock. This is to prevent
	 * races with fxp_intr().
	 */
	bus_teardown_intr(sc->dev, sc->fxp_res[1], sc->ih);
	sc->ih = NULL;

	/* Release our allocated resources. */
	fxp_release(sc);
	return (0);
}