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
struct cphy {int dummy; } ;

/* Variables and functions */
 unsigned int ADVERTISE_1000XFULL ; 
 unsigned int ADVERTISE_1000XHALF ; 
 unsigned int ADVERTISE_1000XPAUSE ; 
 unsigned int ADVERTISE_1000XPSE_ASYM ; 
 unsigned int BMCR_ANENABLE ; 
 unsigned int BMCR_FULLDPLX ; 
 unsigned int BMCR_SPEED100 ; 
 unsigned int BMCR_SPEED1000 ; 
 unsigned int BMSR_ANEGCOMPLETE ; 
 unsigned int BMSR_LSTATUS ; 
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_LPA ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 int PHY_LINK_DOWN ; 
 int PHY_LINK_UP ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int vsc8211_get_link_status_fiber(struct cphy *cphy, int *link_state,
					 int *speed, int *duplex, int *fc)
{
	unsigned int bmcr, status, lpa, adv;
	int err, sp = -1, dplx = -1, pause = 0;

	err = mdio_read(cphy, 0, MII_BMCR, &bmcr);
	if (!err)
		err = mdio_read(cphy, 0, MII_BMSR, &status);
	if (err)
		return err;

	if (link_state) {
		/*
		 * BMSR_LSTATUS is latch-low, so if it is 0 we need to read it
		 * once more to get the current link state.
		 */
		if (!(status & BMSR_LSTATUS))
			err = mdio_read(cphy, 0, MII_BMSR, &status);
		if (err)
			return err;
		*link_state = status & BMSR_LSTATUS ? PHY_LINK_UP :
		    PHY_LINK_DOWN;
	}
	if (!(bmcr & BMCR_ANENABLE)) {
		dplx = (bmcr & BMCR_FULLDPLX) ? DUPLEX_FULL : DUPLEX_HALF;
		if (bmcr & BMCR_SPEED1000)
			sp = SPEED_1000;
		else if (bmcr & BMCR_SPEED100)
			sp = SPEED_100;
		else
			sp = SPEED_10;
	} else if (status & BMSR_ANEGCOMPLETE) {
		err = mdio_read(cphy, 0, MII_LPA, &lpa);
		if (!err)
			err = mdio_read(cphy, 0, MII_ADVERTISE, &adv);
		if (err)
			return err;

		if (adv & lpa & ADVERTISE_1000XFULL) {
			dplx = DUPLEX_FULL;
			sp = SPEED_1000;
		} else if (adv & lpa & ADVERTISE_1000XHALF) {
			dplx = DUPLEX_HALF;
			sp = SPEED_1000;
		}

		if (fc && dplx == DUPLEX_FULL) {
			if (lpa & adv & ADVERTISE_1000XPAUSE)
				pause = PAUSE_RX | PAUSE_TX;
			else if ((lpa & ADVERTISE_1000XPAUSE) &&
				 (adv & lpa & ADVERTISE_1000XPSE_ASYM))
				pause = PAUSE_TX;
			else if ((lpa & ADVERTISE_1000XPSE_ASYM) &&
				 (adv & ADVERTISE_1000XPAUSE))
				pause = PAUSE_RX;
		}
	}
	if (speed)
		*speed = sp;
	if (duplex)
		*duplex = dplx;
	if (fc)
		*fc = pause;
	return 0;
}