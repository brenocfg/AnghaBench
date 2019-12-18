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
 unsigned int ADVERTISE_PAUSE_ASYM ; 
 unsigned int ADVERTISE_PAUSE_CAP ; 
 int AQ_100M_CTRL ; 
 int AQ_ANEG_STAT ; 
 int AQ_LINK_STAT ; 
 unsigned int BMCR_ANENABLE ; 
 unsigned int BMCR_SPEED100 ; 
 unsigned int BMCR_SPEED1000 ; 
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
 int /*<<< orphan*/  MDIO_DEV_ANEG ; 
 int /*<<< orphan*/  MDIO_DEV_PMA_PMD ; 
 int MII_BMCR ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 int PHY_LINK_DOWN ; 
 int PHY_LINK_UP ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int SPEED_10000 ; 
 int mdio_read (struct cphy*,int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static int
aq100x_get_link_status(struct cphy *phy, int *link_state, int *speed, int *duplex,
		       int *fc)
{
	int err;
	unsigned int v, link = 0;

	err = mdio_read(phy, MDIO_DEV_PMA_PMD, AQ_LINK_STAT, &v);
	if (err)
		return (err);
	if (v == 0xffff || !(v & 1))
		goto done;

	err = mdio_read(phy, MDIO_DEV_ANEG, MII_BMCR, &v);
	if (err)
		return (err);
	if (v & 0x8000)
		goto done;
	if (v & BMCR_ANENABLE) {

		err = mdio_read(phy, MDIO_DEV_ANEG, 1, &v);
		if (err)
			return (err);
		if ((v & 0x20) == 0)
			goto done;

		err = mdio_read(phy, MDIO_DEV_ANEG, AQ_ANEG_STAT, &v);
		if (err)
			return (err);

		if (speed) {
			switch (v & 0x6) {
			case 0x6: *speed = SPEED_10000;
				break;
			case 0x4: *speed = SPEED_1000;
				break;
			case 0x2: *speed = SPEED_100;
				break;
			case 0x0: *speed = SPEED_10;
				break;
			}
		}

		if (duplex)
			*duplex = v & 1 ? DUPLEX_FULL : DUPLEX_HALF;

		if (fc) {
			unsigned int lpa, adv;
			err = mdio_read(phy, MDIO_DEV_ANEG, 0x13, &lpa);
			if (!err)
				err = mdio_read(phy, MDIO_DEV_ANEG,
				    AQ_100M_CTRL, &adv);
			if (err)
				return err;

			if (lpa & adv & ADVERTISE_PAUSE_CAP)
				*fc = PAUSE_RX | PAUSE_TX;
			else if (lpa & ADVERTISE_PAUSE_CAP &&
			    lpa & ADVERTISE_PAUSE_ASYM &&
			    adv & ADVERTISE_PAUSE_ASYM)
				*fc = PAUSE_TX;
			else if (lpa & ADVERTISE_PAUSE_ASYM &&
			    adv & ADVERTISE_PAUSE_CAP)
				*fc = PAUSE_RX;
			else
				*fc = 0;
		}

	} else {
		err = mdio_read(phy, MDIO_DEV_PMA_PMD, MII_BMCR, &v);
		if (err)
			return (err);

		v &= BMCR_SPEED1000 | BMCR_SPEED100;
		if (speed) {
			if (v == (BMCR_SPEED1000 | BMCR_SPEED100))
				*speed = SPEED_10000;
			else if (v == BMCR_SPEED1000)
				*speed = SPEED_1000;
			else if (v == BMCR_SPEED100)
				*speed = SPEED_100;
			else
				*speed = SPEED_10;
		}

		if (duplex)
			*duplex = DUPLEX_FULL;
	}

	link = 1;
done:
	if (link_state)
		*link_state = link ? PHY_LINK_UP : PHY_LINK_DOWN;
	return (0);
}