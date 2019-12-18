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
struct smc_softc {TYPE_1__* smc_ifp; scalar_t__ smc_mask; int /*<<< orphan*/  smc_mii_tick_ch; int /*<<< orphan*/  smc_watchdog; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_drv_flags; int /*<<< orphan*/  if_capenable; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCAP_POLLING ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MSK ; 
 int /*<<< orphan*/  RCR ; 
 int /*<<< orphan*/  SMC_ASSERT_LOCKED (struct smc_softc*) ; 
 int /*<<< orphan*/  TCR ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_poll_deregister (TYPE_1__*) ; 
 int /*<<< orphan*/  smc_select_bank (struct smc_softc*,int) ; 
 int /*<<< orphan*/  smc_write_1 (struct smc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_write_2 (struct smc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
smc_stop(struct smc_softc *sc)
{

	SMC_ASSERT_LOCKED(sc);

	/*
	 * Turn off callouts.
	 */
	callout_stop(&sc->smc_watchdog);
	callout_stop(&sc->smc_mii_tick_ch);

	/*
	 * Mask all interrupts.
	 */
	smc_select_bank(sc, 2);
	sc->smc_mask = 0;
	smc_write_1(sc, MSK, 0);
#ifdef DEVICE_POLLING
	ether_poll_deregister(sc->smc_ifp);
	sc->smc_ifp->if_capenable &= ~IFCAP_POLLING;
#endif

	/*
	 * Disable transmit and receive.
	 */
	smc_select_bank(sc, 0);
	smc_write_2(sc, TCR, 0);
	smc_write_2(sc, RCR, 0);

	sc->smc_ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
}