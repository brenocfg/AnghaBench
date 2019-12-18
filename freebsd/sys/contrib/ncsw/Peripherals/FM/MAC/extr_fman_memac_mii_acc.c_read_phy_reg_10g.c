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
typedef  scalar_t__ uint16_t ;
struct memac_mii_access_mem_map {int /*<<< orphan*/  mdio_cfg; int /*<<< orphan*/  mdio_data; int /*<<< orphan*/  mdio_ctrl; int /*<<< orphan*/  mdio_addr; } ;

/* Variables and functions */
 int MDIO_CFG_BSY ; 
 int MDIO_CFG_CLK_DIV_MASK ; 
 int MDIO_CFG_ENC45 ; 
 int MDIO_CFG_HOLD_MASK ; 
 int MDIO_CTL_READ ; 
 int MDIO_DATA_BSY ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static uint32_t read_phy_reg_10g(struct memac_mii_access_mem_map *mii_regs,
	uint8_t phy_addr, uint8_t reg, uint16_t *data)
{
	uint32_t                tmp_reg;

	tmp_reg = ioread32be(&mii_regs->mdio_cfg);
	/* Leave only MDIO_CLK_DIV bits set on */
	tmp_reg &= MDIO_CFG_CLK_DIV_MASK;
	/* Set maximum MDIO_HOLD value to allow phy to see
	change of data signal */
	tmp_reg |= MDIO_CFG_HOLD_MASK;
	/* Add 10G interface mode */
	tmp_reg |= MDIO_CFG_ENC45;
	iowrite32be(tmp_reg, &mii_regs->mdio_cfg);

	/* Wait for command completion */
	while ((ioread32be(&mii_regs->mdio_cfg)) & MDIO_CFG_BSY)
		udelay(1);

	/* Specify phy and register to be accessed */
	iowrite32be(phy_addr, &mii_regs->mdio_ctrl);
	iowrite32be(reg, &mii_regs->mdio_addr);
	wmb();

	while ((ioread32be(&mii_regs->mdio_cfg)) & MDIO_CFG_BSY)
		udelay(1);

	/* Read cycle */
	tmp_reg = phy_addr;
	tmp_reg |= MDIO_CTL_READ;
	iowrite32be(tmp_reg, &mii_regs->mdio_ctrl);
	wmb();

	/* Wait for data to be available */
	while ((ioread32be(&mii_regs->mdio_data)) & MDIO_DATA_BSY)
		udelay(1);

	*data =  (uint16_t)ioread32be(&mii_regs->mdio_data);

	/* Check if there was an error */
	return ioread32be(&mii_regs->mdio_cfg);
}