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
struct cphy {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_T3DBG_GPIO_EN ; 
 int /*<<< orphan*/  F_GPIO6_OUT_VAL ; 
 int /*<<< orphan*/  MDIO_DEV_PMA_PMD ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  msleep (int) ; 
 int t3_mdio_change_bits (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int t3_phy_reset (struct cphy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t3_set_reg_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ael1006_reset(struct cphy *phy, int wait)
{
	int err;

	err = t3_phy_reset(phy, MDIO_DEV_PMA_PMD, wait);
	if (err)
		return err;

	t3_set_reg_field(phy->adapter, A_T3DBG_GPIO_EN, 
			 F_GPIO6_OUT_VAL, 0);

	msleep(125);

	t3_set_reg_field(phy->adapter, A_T3DBG_GPIO_EN, 
			 F_GPIO6_OUT_VAL, F_GPIO6_OUT_VAL);

	msleep(125);

	err = t3_phy_reset(phy, MDIO_DEV_PMA_PMD, wait);
	if (err)
		return err;

	msleep(125);

	err = t3_mdio_change_bits(phy, MDIO_DEV_PMA_PMD, MII_BMCR, 1, 1);
	if (err)
		return err;
	
	msleep(125);

	err = t3_mdio_change_bits(phy, MDIO_DEV_PMA_PMD, MII_BMCR, 1, 0);

	return err;
	   
}