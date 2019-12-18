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
struct usb_ether {int /*<<< orphan*/  ue_dev; } ;
struct mii_data {int dummy; } ;
struct axe_softc {int sc_flags; } ;

/* Variables and functions */
 int AXE_FLAG_LINK ; 
 int /*<<< orphan*/  AXE_LOCK_ASSERT (struct axe_softc*,int /*<<< orphan*/ ) ; 
 struct mii_data* GET_MII (struct axe_softc*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  axe_miibus_statchg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axe_start (struct usb_ether*) ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 
 struct axe_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
axe_tick(struct usb_ether *ue)
{
	struct axe_softc *sc = uether_getsc(ue);
	struct mii_data *mii = GET_MII(sc);

	AXE_LOCK_ASSERT(sc, MA_OWNED);

	mii_tick(mii);
	if ((sc->sc_flags & AXE_FLAG_LINK) == 0) {
		axe_miibus_statchg(ue->ue_dev);
		if ((sc->sc_flags & AXE_FLAG_LINK) != 0)
			axe_start(ue);
	}
}