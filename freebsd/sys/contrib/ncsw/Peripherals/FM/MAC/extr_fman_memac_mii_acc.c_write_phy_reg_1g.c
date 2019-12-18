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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct memac_mii_access_mem_map {int /*<<< orphan*/  mdio_data; int /*<<< orphan*/  mdio_cfg; int /*<<< orphan*/  mdio_ctrl; } ;

/* Variables and functions */
 int MDIO_CFG_BSY ; 
 int MDIO_CFG_CLK_DIV_MASK ; 
 int MDIO_CFG_HOLD_MASK ; 
 int MDIO_CTL_PHY_ADDR_SHIFT ; 
 int MDIO_DATA_BSY ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void write_phy_reg_1g(struct memac_mii_access_mem_map *mii_regs,
	uint8_t phy_addr, uint8_t reg, uint16_t data)
{
	uint32_t                tmp_reg;

	/* Leave only MDIO_CLK_DIV and MDIO_HOLD bits set on */
	tmp_reg = ioread32be(&mii_regs->mdio_cfg);
	tmp_reg &= (MDIO_CFG_CLK_DIV_MASK | MDIO_CFG_HOLD_MASK);
	iowrite32be(tmp_reg, &mii_regs->mdio_cfg);

	/* Wait for command completion */
	while ((ioread32be(&mii_regs->mdio_cfg)) & MDIO_CFG_BSY)
		udelay(1);

	/* Write transaction */
	tmp_reg = (phy_addr << MDIO_CTL_PHY_ADDR_SHIFT);
	tmp_reg |= reg;
	iowrite32be(tmp_reg, &mii_regs->mdio_ctrl);

	while ((ioread32be(&mii_regs->mdio_cfg)) & MDIO_CFG_BSY)
		udelay(1);

	iowrite32be(data, &mii_regs->mdio_data);

	wmb();

	/* Wait for write transaction to end */
	while ((ioread32be(&mii_regs->mdio_data)) & MDIO_DATA_BSY)
		udelay(1);
}