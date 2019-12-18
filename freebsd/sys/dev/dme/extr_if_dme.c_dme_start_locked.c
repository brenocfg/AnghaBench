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
struct ifnet {int if_drv_flags; struct dme_softc* if_softc; } ;
struct dme_softc {scalar_t__ dme_txbusy; scalar_t__ dme_txready; TYPE_1__* dme_ifp; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DME_ASSERT_LOCKED (struct dme_softc*) ; 
 int /*<<< orphan*/  DTR3 (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  dme_prepare (struct dme_softc*) ; 
 int /*<<< orphan*/  dme_transmit (struct dme_softc*) ; 

__attribute__((used)) static void
dme_start_locked(struct ifnet *ifp)
{
	struct dme_softc *sc;

	sc = ifp->if_softc;
	DME_ASSERT_LOCKED(sc);

	if ((ifp->if_drv_flags & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING)
		return;

	DTR3("dme_start, flags %#x busy %d ready %d",
	    sc->dme_ifp->if_drv_flags, sc->dme_txbusy, sc->dme_txready);
	KASSERT(sc->dme_txbusy == 0 || sc->dme_txready == 0,
	    ("dme: send without empty queue\n"));

	dme_prepare(sc);

	if (sc->dme_txbusy == 0) {
		/* We are ready to transmit right away */
		dme_transmit(sc);
		dme_prepare(sc); /* Prepare next one */
	}
	/*
	 * We need to wait until the current packet has
	 * been transmitted.
	 */
	if (sc->dme_txready != 0)
		ifp->if_drv_flags |= IFF_DRV_OACTIVE;
}