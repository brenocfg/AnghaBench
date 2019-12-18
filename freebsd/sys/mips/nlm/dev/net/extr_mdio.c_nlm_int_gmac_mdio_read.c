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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ INT_MDIO_CTRL ; 
 int INT_MDIO_CTRL_CMD_LOAD ; 
 int INT_MDIO_CTRL_DEVTYPE_POS ; 
 int INT_MDIO_CTRL_LOAD_POS ; 
 int INT_MDIO_CTRL_MCDIV_POS ; 
 int INT_MDIO_CTRL_MIIM_POS ; 
 int INT_MDIO_CTRL_OP_POS ; 
 int INT_MDIO_CTRL_PHYADDR_POS ; 
 int INT_MDIO_CTRL_SMP ; 
 int INT_MDIO_CTRL_ST_POS ; 
 int INT_MDIO_CTRL_TA_POS ; 
 int INT_MDIO_CTRL_XDIV_POS ; 
 scalar_t__ INT_MDIO_RD_STAT ; 
 int INT_MDIO_STAT_MBSY ; 
 int /*<<< orphan*/  NAE_REG (int,int,scalar_t__) ; 
 int nlm_read_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
nlm_int_gmac_mdio_read(uint64_t nae_base, int bus, int block,
    int intf_type, int phyaddr, int regidx)
{
	uint32_t mdio_ld_cmd;
	uint32_t ctrlval;

	ctrlval = INT_MDIO_CTRL_SMP		|
	    (phyaddr << INT_MDIO_CTRL_PHYADDR_POS) |
	    (regidx << INT_MDIO_CTRL_DEVTYPE_POS) |
	    (2 << INT_MDIO_CTRL_OP_POS)		|
	    (1 << INT_MDIO_CTRL_ST_POS)		|
	    (7 << INT_MDIO_CTRL_XDIV_POS)	|
	    (2 << INT_MDIO_CTRL_TA_POS)		|
	    (2 << INT_MDIO_CTRL_MIIM_POS)	|
	    (1 << INT_MDIO_CTRL_MCDIV_POS);

	mdio_ld_cmd = nlm_read_nae_reg(nae_base,
	    NAE_REG(block, intf_type, (INT_MDIO_CTRL + bus * 4)));
	if (mdio_ld_cmd & INT_MDIO_CTRL_CMD_LOAD) {
		nlm_write_nae_reg(nae_base,
		    NAE_REG(block, intf_type, (INT_MDIO_CTRL + bus*4)),
		    (mdio_ld_cmd & ~INT_MDIO_CTRL_CMD_LOAD));
	}

	nlm_write_nae_reg(nae_base,
	    NAE_REG(block, intf_type, (INT_MDIO_CTRL + bus * 4)),
	    ctrlval);

	/* Toggle Load Cmd Bit */
	nlm_write_nae_reg(nae_base,
	    NAE_REG(block, intf_type, (INT_MDIO_CTRL + bus * 4)),
	    ctrlval | (1 << INT_MDIO_CTRL_LOAD_POS));

	/* poll master busy bit until it is not busy */
	while(nlm_read_nae_reg(nae_base,
	    NAE_REG(block, intf_type, (INT_MDIO_RD_STAT + bus * 4))) &
	    INT_MDIO_STAT_MBSY) {
	}

	nlm_write_nae_reg(nae_base,
	    NAE_REG(block, intf_type, (INT_MDIO_CTRL + bus * 4)),
	    ctrlval);

	/* Read the data back */
	return nlm_read_nae_reg(nae_base,
	    NAE_REG(block, intf_type, (INT_MDIO_RD_STAT + bus * 4)));
}