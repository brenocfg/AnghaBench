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
 int /*<<< orphan*/  AEL100X_TX_DISABLE ; 
 int /*<<< orphan*/  BMCR_PDOWN ; 
 int /*<<< orphan*/  MDIO_DEV_PMA_PMD ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int mdio_write (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int t3_mdio_change_bits (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ael1002_power_down(struct cphy *phy, int enable)
{
	int err;

	err = mdio_write(phy, MDIO_DEV_PMA_PMD, AEL100X_TX_DISABLE, !!enable);
	if (!err)
		err = t3_mdio_change_bits(phy, MDIO_DEV_PMA_PMD, MII_BMCR,
					  BMCR_PDOWN, enable ? BMCR_PDOWN : 0);
	return err;
}