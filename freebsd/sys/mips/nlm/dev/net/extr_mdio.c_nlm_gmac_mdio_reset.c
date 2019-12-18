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
 scalar_t__ EXT_G0_MDIO_CTRL ; 
 int EXT_G_MDIO_DIV ; 
 int EXT_G_MDIO_DIV_WITH_HW_DIV64 ; 
 int EXT_G_MDIO_MMRST ; 
 int /*<<< orphan*/  NAE_REG (int,int,scalar_t__) ; 
 scalar_t__ nlm_is_xlp3xx_ax () ; 
 scalar_t__ nlm_is_xlp8xx_ax () ; 
 scalar_t__ nlm_is_xlp8xx_b0 () ; 
 int nlm_read_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
nlm_gmac_mdio_reset(uint64_t nae_base, int bus, int block,
    int intf_type)
{
	uint32_t ctrlval;

	ctrlval = nlm_read_nae_reg(nae_base,
	    NAE_REG(block, intf_type, (EXT_G0_MDIO_CTRL+bus*4)));

	if (nlm_is_xlp8xx_ax() || nlm_is_xlp8xx_b0() || nlm_is_xlp3xx_ax())
		ctrlval |= EXT_G_MDIO_DIV;
	else
		ctrlval |= EXT_G_MDIO_DIV_WITH_HW_DIV64;

	nlm_write_nae_reg(nae_base,
	    NAE_REG(block, intf_type, (EXT_G0_MDIO_CTRL + bus * 4)),
	    EXT_G_MDIO_MMRST | ctrlval);
	nlm_write_nae_reg(nae_base,
	    NAE_REG(block, intf_type, (EXT_G0_MDIO_CTRL + bus * 4)), ctrlval);
	return (0);
}