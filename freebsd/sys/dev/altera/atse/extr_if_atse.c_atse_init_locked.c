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
typedef  int /*<<< orphan*/  uint8_t ;
struct mii_data {int dummy; } ;
struct ifnet {int if_drv_flags; } ;
struct atse_softc {int /*<<< orphan*/  atse_tick; int /*<<< orphan*/  atse_flags; int /*<<< orphan*/  atse_miibus; int /*<<< orphan*/  atse_eth_addr; struct ifnet* atse_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATSE_FLAGS_LINK ; 
 int /*<<< orphan*/  ATSE_LOCK_ASSERT (struct atse_softc*) ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/ * IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  atse_reset (struct atse_softc*) ; 
 int /*<<< orphan*/  atse_rxfilter_locked (struct atse_softc*) ; 
 int /*<<< orphan*/  atse_stop_locked (struct atse_softc*) ; 
 int /*<<< orphan*/  atse_tick ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct atse_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 

__attribute__((used)) static void
atse_init_locked(struct atse_softc *sc)
{
	struct ifnet *ifp;
	struct mii_data *mii;
	uint8_t *eaddr;

	ATSE_LOCK_ASSERT(sc);
	ifp = sc->atse_ifp;

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
		return;
	}

	/*
	 * Must update the ether address if changed.  Given we do not handle
	 * in atse_ioctl() but it's in the general framework, just always
	 * do it here before atse_reset().
	 */
	eaddr = IF_LLADDR(sc->atse_ifp);
	bcopy(eaddr, &sc->atse_eth_addr, ETHER_ADDR_LEN);

	/* Make things frind to halt, cleanup, ... */
	atse_stop_locked(sc);

	atse_reset(sc);

	/* ... and fire up the engine again. */
	atse_rxfilter_locked(sc);

	sc->atse_flags &= ATSE_FLAGS_LINK;	/* Preserve. */

	mii = device_get_softc(sc->atse_miibus);

	sc->atse_flags &= ~ATSE_FLAGS_LINK;
	mii_mediachg(mii);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	callout_reset(&sc->atse_tick, hz, atse_tick, sc);
}