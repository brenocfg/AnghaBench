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
struct rdcphy_softc {int /*<<< orphan*/  mii_link_tick; } ;
struct mii_softc {int dummy; } ;
struct TYPE_2__ {struct ifmedia_entry* ifm_cur; } ;
struct mii_data {int mii_media_active; int /*<<< orphan*/  mii_media_status; TYPE_1__ mii_media; } ;
struct ifmedia_entry {int /*<<< orphan*/  ifm_media; } ;

/* Variables and functions */
 int /*<<< orphan*/  EJUSTRETURN ; 
#define  IFM_100_TX 132 
#define  IFM_10_T 131 
 int /*<<< orphan*/  IFM_AUTO ; 
 int IFM_ETHER ; 
 int IFM_NONE ; 
 int /*<<< orphan*/  IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
#define  MII_MEDIACHG 130 
#define  MII_POLLSTAT 129 
#define  MII_TICK 128 
 int /*<<< orphan*/  PHY_STATUS (struct mii_softc*) ; 
 int /*<<< orphan*/  RDCPHY_MANNEG_TICK ; 
 int /*<<< orphan*/  mii_phy_setmedia (struct mii_softc*) ; 
 int /*<<< orphan*/  mii_phy_tick (struct mii_softc*) ; 
 int /*<<< orphan*/  mii_phy_update (struct mii_softc*,int const) ; 

__attribute__((used)) static int
rdcphy_service(struct mii_softc *sc, struct mii_data *mii, int cmd)
{
	struct rdcphy_softc *rsc;
	struct ifmedia_entry *ife;

	rsc = (struct rdcphy_softc *)sc;
	ife = mii->mii_media.ifm_cur;

	switch (cmd) {
	case MII_POLLSTAT:
		break;

	case MII_MEDIACHG:
		mii_phy_setmedia(sc);
		switch (IFM_SUBTYPE(ife->ifm_media)) {
		case IFM_100_TX:
		case IFM_10_T:
			/*
			 * Report fake lost link event to parent
			 * driver.  This will stop MAC of parent
			 * driver and make it possible to reconfigure
			 * MAC after completion of link establishment.
			 * Note, the parent MAC seems to require
			 * restarting MAC when underlying any PHY
			 * configuration was changed even if the
			 * resolved speed/duplex was not changed at
			 * all.
			 */
			mii->mii_media_status = 0;
			mii->mii_media_active = IFM_ETHER | IFM_NONE;
			rsc->mii_link_tick = RDCPHY_MANNEG_TICK;
			/* Immediately report link down. */
			mii_phy_update(sc, MII_MEDIACHG);
			return (0);
		default:
			break;
		}
		break;

	case MII_TICK:
		if (mii_phy_tick(sc) == EJUSTRETURN)
			return (0);
		if (IFM_SUBTYPE(ife->ifm_media) != IFM_AUTO) {
			/*
			 * It seems the PHY hardware does not correctly
			 * report link status changes when manual link
			 * configuration is in progress.  It is also
			 * possible for the PHY to complete establishing
			 * a link within one second such that mii(4)
			 * did not notice the link change.  To workaround
			 * the issue, emulate lost link event and wait
			 * for 3 seconds when manual link configuration
			 * is in progress.  3 seconds would be long
			 * enough to absorb transient link flips.
			 */
			if (rsc->mii_link_tick > 0) {
				rsc->mii_link_tick--;
				return (0);
			}
		}
		break;
	}

	/* Update the media status. */
	PHY_STATUS(sc);

	/* Callback if something changed. */
	mii_phy_update(sc, cmd);
	return (0);
}