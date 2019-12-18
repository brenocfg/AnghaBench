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
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_RESET ; 
 int BMCR_SPEED100 ; 
 int BMCR_SPEED1000 ; 
 int DUPLEX_FULL ; 
 int EINVAL ; 
 int /*<<< orphan*/  MDIO_DEV_ANEG ; 
 int /*<<< orphan*/  MDIO_DEV_PMA_PMD ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int SPEED_10000 ; 
 int t3_mdio_change_bits (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
aq100x_set_speed_duplex(struct cphy *phy, int speed, int duplex)
{
	int err, set;

	if (speed == SPEED_100)
		set = BMCR_SPEED100;
	else if (speed == SPEED_1000)
		set = BMCR_SPEED1000;
	else if (speed == SPEED_10000)
		set = BMCR_SPEED1000 | BMCR_SPEED100;
	else
		return (EINVAL);

	if (duplex != DUPLEX_FULL)
		return (EINVAL);

	err = t3_mdio_change_bits(phy, MDIO_DEV_ANEG, MII_BMCR,
	    BMCR_RESET | BMCR_ANENABLE | BMCR_ANRESTART, 0);
	if (err)
		return (err);

	err = t3_mdio_change_bits(phy, MDIO_DEV_PMA_PMD, MII_BMCR,
	    BMCR_SPEED1000 | BMCR_SPEED100, set);
	if (err)
		return (err);

	return (0);
}