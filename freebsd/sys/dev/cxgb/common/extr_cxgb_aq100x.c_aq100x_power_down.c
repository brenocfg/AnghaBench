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
struct cphy {int /*<<< orphan*/  addr; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMCR_PDOWN ; 
 unsigned int BMCR_RESET ; 
 int /*<<< orphan*/  CH_WARN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MDIO_DEV_PMA_PMD ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int t3_mdio_change_bits (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aq100x_power_down(struct cphy *phy, int off)
{
	int err, wait = 500;
	unsigned int v;

	err = t3_mdio_change_bits(phy, MDIO_DEV_PMA_PMD, MII_BMCR, BMCR_PDOWN,
	    off ? BMCR_PDOWN : 0);
	if (err || off)
		return (err);

	msleep(300);
	do {
		err = mdio_read(phy, MDIO_DEV_PMA_PMD, MII_BMCR, &v);
		if (err)
			return (err);
		v &= BMCR_RESET;
		if (v)
			msleep(10);
	} while (v && --wait);
	if (v) {
		CH_WARN(phy->adapter, "PHY%d: power-up timed out (0x%x).\n",
		    phy->addr, v);
		return (ETIMEDOUT);
	}

	return (0);
}