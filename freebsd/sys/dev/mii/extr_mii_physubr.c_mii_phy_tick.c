#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mii_softc {scalar_t__ mii_ticks; scalar_t__ mii_anegticks; TYPE_2__* mii_pdata; } ;
struct ifmedia_entry {int /*<<< orphan*/  ifm_media; } ;
struct TYPE_3__ {struct ifmedia_entry* ifm_cur; } ;
struct TYPE_4__ {TYPE_1__ mii_media; } ;

/* Variables and functions */
 int BMSR_LINK ; 
 int EJUSTRETURN ; 
 scalar_t__ IFM_AUTO ; 
 scalar_t__ IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ MII_ANEGTICKS_GIGE ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_RESET (struct mii_softc*) ; 
 int /*<<< orphan*/  mii_phy_auto (struct mii_softc*) ; 

int
mii_phy_tick(struct mii_softc *sc)
{
	struct ifmedia_entry *ife = sc->mii_pdata->mii_media.ifm_cur;
	int reg;

	/*
	 * If we're not doing autonegotiation, we don't need to do
	 * any extra work here.  However, we need to check the link
	 * status so we can generate an announcement if the status
	 * changes.
	 */
	if (IFM_SUBTYPE(ife->ifm_media) != IFM_AUTO) {
		sc->mii_ticks = 0;	/* reset autonegotiation timer. */
		return (0);
	}

	/* Read the status register twice; BMSR_LINK is latch-low. */
	reg = PHY_READ(sc, MII_BMSR) | PHY_READ(sc, MII_BMSR);
	if ((reg & BMSR_LINK) != 0) {
		sc->mii_ticks = 0;	/* reset autonegotiation timer. */
		/* See above. */
		return (0);
	}

	/* Announce link loss right after it happens */
	if (sc->mii_ticks++ == 0)
		return (0);

	/* XXX: use default value if phy driver did not set mii_anegticks */
	if (sc->mii_anegticks == 0)
		sc->mii_anegticks = MII_ANEGTICKS_GIGE;

	/* Only retry autonegotiation every mii_anegticks ticks. */
	if (sc->mii_ticks <= sc->mii_anegticks)
		return (EJUSTRETURN);

	sc->mii_ticks = 0;
	PHY_RESET(sc);
	mii_phy_auto(sc);
	return (0);
}