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
struct nf10bmac_softc {int /*<<< orphan*/  nf10bmac_flags; struct ifnet* nf10bmac_ifp; int /*<<< orphan*/  nf10bmac_tick; scalar_t__ nf10bmac_watchdog_timer; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  NF10BMAC_FLAGS_LINK ; 
 int /*<<< orphan*/  NF10BMAC_LOCK_ASSERT (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  NF10BMAC_RX_INTR_CLEAR_DIS (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_link_state_change (struct ifnet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nf10bmac_stop_locked(struct nf10bmac_softc *sc)
{
	struct ifnet *ifp;

	NF10BMAC_LOCK_ASSERT(sc);

#ifdef ENABLE_WATCHDOG
	sc->nf10bmac_watchdog_timer = 0;
	callout_stop(&sc->nf10bmac_tick);
#endif

	ifp = sc->nf10bmac_ifp;
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	NF10BMAC_RX_INTR_CLEAR_DIS(sc);

	sc->nf10bmac_flags &= ~NF10BMAC_FLAGS_LINK;
	if_link_state_change(ifp, LINK_STATE_DOWN);

	return (0);
}