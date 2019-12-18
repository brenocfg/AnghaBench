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
struct TYPE_2__ {scalar_t__ queued; } ;
struct nfe_softc {scalar_t__ nfe_watchdog_timer; int nfe_force_tx; int rxtxctl; TYPE_1__ txq; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  NFE_RXTX_CTL ; 
 int NFE_RXTX_KICKTX ; 
 int /*<<< orphan*/  NFE_WRITE (struct nfe_softc*,int /*<<< orphan*/ ,int) ; 
 struct nfe_softc* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  if_sendq_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfe_init_locked (struct nfe_softc*) ; 
 int /*<<< orphan*/  nfe_start_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfe_txeof (struct nfe_softc*) ; 

__attribute__((used)) static void
nfe_watchdog(if_t ifp)
{
	struct nfe_softc *sc = if_getsoftc(ifp);

	if (sc->nfe_watchdog_timer == 0 || --sc->nfe_watchdog_timer)
		return;

	/* Check if we've lost Tx completion interrupt. */
	nfe_txeof(sc);
	if (sc->txq.queued == 0) {
		if_printf(ifp, "watchdog timeout (missed Tx interrupts) "
		    "-- recovering\n");
		if (!if_sendq_empty(ifp))
			nfe_start_locked(ifp);
		return;
	}
	/* Check if we've lost start Tx command. */
	sc->nfe_force_tx++;
	if (sc->nfe_force_tx <= 3) {
		/*
		 * If this is the case for watchdog timeout, the following
		 * code should go to nfe_txeof().
		 */
		NFE_WRITE(sc, NFE_RXTX_CTL, NFE_RXTX_KICKTX | sc->rxtxctl);
		return;
	}
	sc->nfe_force_tx = 0;

	if_printf(ifp, "watchdog timeout\n");

	if_setdrvflagbits(ifp, 0, IFF_DRV_RUNNING);
	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	nfe_init_locked(sc);
}