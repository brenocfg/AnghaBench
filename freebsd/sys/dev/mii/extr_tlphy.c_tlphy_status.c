#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct mii_data* mii_pdata; } ;
struct tlphy_softc {TYPE_3__ sc_mii; } ;
struct mii_softc {int dummy; } ;
struct TYPE_5__ {TYPE_1__* ifm_cur; } ;
struct mii_data {int mii_media_active; int /*<<< orphan*/  mii_media_status; TYPE_2__ mii_media; } ;
struct TYPE_4__ {int ifm_media; } ;

/* Variables and functions */
 int BMCR_FDX ; 
 int BMCR_ISO ; 
 int BMCR_LOOP ; 
 int BMSR_LINK ; 
 int CTRL_AUISEL ; 
 int IFM_10_T ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 
 int IFM_HDX ; 
 int IFM_LOOP ; 
 int IFM_NONE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_TLPHY_CTRL ; 
 int PHY_READ (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int mii_phy_flowstatus (struct mii_softc*) ; 

__attribute__((used)) static void
tlphy_status(struct mii_softc *self)
{
	struct tlphy_softc *sc = (struct tlphy_softc *)self;
	struct mii_data *mii = sc->sc_mii.mii_pdata;
	int bmsr, bmcr, tlctrl;

	mii->mii_media_status = IFM_AVALID;
	mii->mii_media_active = IFM_ETHER;

	bmcr = PHY_READ(&sc->sc_mii, MII_BMCR);
	if (bmcr & BMCR_ISO) {
		mii->mii_media_active |= IFM_NONE;
		mii->mii_media_status = 0;
		return;
	}

	tlctrl = PHY_READ(&sc->sc_mii, MII_TLPHY_CTRL);
	if (tlctrl & CTRL_AUISEL) {
		mii->mii_media_status = 0;
		mii->mii_media_active = mii->mii_media.ifm_cur->ifm_media;
		return;
	}

	bmsr = PHY_READ(&sc->sc_mii, MII_BMSR) |
	    PHY_READ(&sc->sc_mii, MII_BMSR);
	if (bmsr & BMSR_LINK)
		mii->mii_media_status |= IFM_ACTIVE;

	if (bmcr & BMCR_LOOP)
		mii->mii_media_active |= IFM_LOOP;

	/*
	 * Grr, braindead ThunderLAN PHY doesn't have any way to
	 * tell which media is actually active.  (Note it also
	 * doesn't self-configure after autonegotiation.)  We
	 * just have to report what's in the BMCR.
	 */
	if (bmcr & BMCR_FDX)
		mii->mii_media_active |= IFM_FDX | mii_phy_flowstatus(self);
	else
		mii->mii_media_active |= IFM_HDX;
	mii->mii_media_active |= IFM_10_T;
}