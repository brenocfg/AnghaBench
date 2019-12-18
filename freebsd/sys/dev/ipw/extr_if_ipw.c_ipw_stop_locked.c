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
struct ipw_softc {int /*<<< orphan*/  flags; scalar_t__ sc_tx_timer; int /*<<< orphan*/ * stbd_list; int /*<<< orphan*/  sc_wdtimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct ipw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPW_CSR_RST ; 
 int /*<<< orphan*/  IPW_FLAG_RUNNING ; 
 int /*<<< orphan*/  IPW_LOCK_ASSERT (struct ipw_softc*) ; 
 int IPW_NTBD ; 
 int /*<<< orphan*/  IPW_RST_SW_RESET ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipw_release_sbd (struct ipw_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipw_stop_master (struct ipw_softc*) ; 

__attribute__((used)) static void
ipw_stop_locked(struct ipw_softc *sc)
{
	int i;

	IPW_LOCK_ASSERT(sc);

	callout_stop(&sc->sc_wdtimer);
	ipw_stop_master(sc);

	CSR_WRITE_4(sc, IPW_CSR_RST, IPW_RST_SW_RESET);

	/*
	 * Release tx buffers.
	 */
	for (i = 0; i < IPW_NTBD; i++)
		ipw_release_sbd(sc, &sc->stbd_list[i]);

	sc->sc_tx_timer = 0;
	sc->flags &= ~IPW_FLAG_RUNNING;
}