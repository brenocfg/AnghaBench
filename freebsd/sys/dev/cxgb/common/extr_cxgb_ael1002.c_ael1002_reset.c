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
struct cphy {int modtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  AEL1002_LB_EN ; 
 int /*<<< orphan*/  AEL1002_PWR_DOWN_HI ; 
 int /*<<< orphan*/  AEL1002_PWR_DOWN_LO ; 
 int /*<<< orphan*/  AEL1002_XFI_EQL ; 
 int /*<<< orphan*/  AEL100X_TX_CONFIG1 ; 
 int /*<<< orphan*/  MDIO_DEV_PMA_PMD ; 
 int ael1002_get_module_type (struct cphy*,int) ; 
 int ael1002_power_down (struct cphy*,int /*<<< orphan*/ ) ; 
 int mdio_write (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int t3_mdio_change_bits (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ael1002_reset(struct cphy *phy, int wait)
{
	int err;

	if ((err = ael1002_power_down(phy, 0)) ||
	    (err = mdio_write(phy, MDIO_DEV_PMA_PMD, AEL100X_TX_CONFIG1, 1)) ||
	    (err = mdio_write(phy, MDIO_DEV_PMA_PMD, AEL1002_PWR_DOWN_HI, 0)) ||
	    (err = mdio_write(phy, MDIO_DEV_PMA_PMD, AEL1002_PWR_DOWN_LO, 0)) ||
	    (err = mdio_write(phy, MDIO_DEV_PMA_PMD, AEL1002_XFI_EQL, 0x18)) ||
	    (err = t3_mdio_change_bits(phy, MDIO_DEV_PMA_PMD, AEL1002_LB_EN,
				       0, 1 << 5)))
		return err;

	err = ael1002_get_module_type(phy, 300);
	if (err >= 0)
		phy->modtype = err;

	return 0;
}