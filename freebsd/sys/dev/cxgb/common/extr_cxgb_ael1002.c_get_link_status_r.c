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
 int DUPLEX_FULL ; 
 int /*<<< orphan*/  MDIO_DEV_PCS ; 
 int /*<<< orphan*/  MDIO_DEV_PMA_PMD ; 
 int /*<<< orphan*/  MDIO_DEV_XGXS ; 
 int /*<<< orphan*/  PCS_STAT1_R ; 
 int PHY_LINK_DOWN ; 
 int PHY_LINK_PARTIAL ; 
 int PHY_LINK_UP ; 
 int /*<<< orphan*/  PMD_RSD ; 
 int SPEED_10000 ; 
 int /*<<< orphan*/  XS_LN_STAT ; 
 int mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int get_link_status_r(struct cphy *phy, int *link_state, int *speed,
			     int *duplex, int *fc)
{
	if (link_state) {
		unsigned int stat0, stat1, stat2;
		int err = mdio_read(phy, MDIO_DEV_PMA_PMD, PMD_RSD, &stat0);

		if (!err)
			err = mdio_read(phy, MDIO_DEV_PCS, PCS_STAT1_R, &stat1);
		if (!err)
			err = mdio_read(phy, MDIO_DEV_XGXS, XS_LN_STAT, &stat2);
		if (err)
			return err;

		stat0 &= 1;
		stat1 &= 1;
		stat2 = (stat2 >> 12) & 1;
		if (stat0 & stat1 & stat2)
			*link_state = PHY_LINK_UP;
		else if (stat0 == 1 && stat1 == 0 && stat2 == 1)
			*link_state = PHY_LINK_PARTIAL;
		else
			*link_state = PHY_LINK_DOWN;
	}
	if (speed)
		*speed = SPEED_10000;
	if (duplex)
		*duplex = DUPLEX_FULL;
	return 0;
}