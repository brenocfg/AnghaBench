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
struct reg_val {int member_2; int member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct cphy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AEL2020_GPIO_CTRL ; 
 int AEL2020_GPIO_LSTAT ; 
 int AEL2020_GPIO_MODDET ; 
 int /*<<< orphan*/  MDIO_DEV_PMA_PMD ; 
 int set_phy_regs (struct cphy*,struct reg_val*) ; 
 int t3_phy_lasi_intr_disable (struct cphy*) ; 

__attribute__((used)) static int ael2020_intr_disable(struct cphy *phy)
{
	struct reg_val regs[] = {
		{ MDIO_DEV_PMA_PMD, AEL2020_GPIO_CTRL,
			0xffff, 0xb << (AEL2020_GPIO_LSTAT*4) },

		{ MDIO_DEV_PMA_PMD, AEL2020_GPIO_CTRL,
			0xffff, 0x1 << (AEL2020_GPIO_MODDET*4) },

		/* end */
		{ 0, 0, 0, 0 }
	};
	int err;

	err = set_phy_regs(phy, regs);
	if (err)
		return err;

	/* disable standard Link Alarm Status Interrupts */
	return t3_phy_lasi_intr_disable(phy);
}