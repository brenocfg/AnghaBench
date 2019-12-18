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
struct smc_softc {int /*<<< orphan*/ * smc_mii_tick; int /*<<< orphan*/  smc_mii_tick_ch; struct ifnet* smc_ifp; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_capenable; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCAP_POLLING ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  SMC_ASSERT_LOCKED (struct smc_softc*) ; 
 int /*<<< orphan*/  SMC_LOCK (struct smc_softc*) ; 
 int /*<<< orphan*/  SMC_UNLOCK (struct smc_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct smc_softc*) ; 
 int /*<<< orphan*/  ether_poll_register (int /*<<< orphan*/ ,struct ifnet*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  smc_enable (struct smc_softc*) ; 
 int /*<<< orphan*/  smc_poll ; 
 int /*<<< orphan*/  smc_reset (struct smc_softc*) ; 
 int /*<<< orphan*/  smc_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
smc_init_locked(struct smc_softc *sc)
{
	struct ifnet	*ifp;

	SMC_ASSERT_LOCKED(sc);
	ifp = sc->smc_ifp;
	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;

	smc_reset(sc);
	smc_enable(sc);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	smc_start_locked(ifp);

	if (sc->smc_mii_tick != NULL)
		callout_reset(&sc->smc_mii_tick_ch, hz, sc->smc_mii_tick, sc);

#ifdef DEVICE_POLLING
	SMC_UNLOCK(sc);
	ether_poll_register(smc_poll, ifp);
	SMC_LOCK(sc);
	ifp->if_capenable |= IFCAP_POLLING;
#endif
}