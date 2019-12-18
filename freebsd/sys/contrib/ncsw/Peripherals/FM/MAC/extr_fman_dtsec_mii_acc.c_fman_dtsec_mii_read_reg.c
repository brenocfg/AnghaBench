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
struct dtsec_mii_reg {int /*<<< orphan*/  miimcom; int /*<<< orphan*/  miimstat; int /*<<< orphan*/  miimind; int /*<<< orphan*/  miimadd; int /*<<< orphan*/  miimcfg; } ;

/* Variables and functions */
 int ENXIO ; 
 int MIIMADD_PHY_ADDR_SHIFT ; 
 int MIIMCOM_READ_CYCLE ; 
 int MIIMIND_BUSY ; 
 scalar_t__ dtsec_mii_get_div (int) ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

int fman_dtsec_mii_read_reg(struct dtsec_mii_reg *regs, uint8_t  addr,
		uint8_t reg, uint16_t *data, uint16_t dtsec_freq)
{
	uint32_t	tmp;

	/* Setup the MII Mgmt clock speed */
	iowrite32be((uint32_t)dtsec_mii_get_div(dtsec_freq), &regs->miimcfg);
	wmb();

	/* Setting up the MII Management Address Register */
	tmp = (uint32_t)((addr << MIIMADD_PHY_ADDR_SHIFT) | reg);
	iowrite32be(tmp, &regs->miimadd);
	wmb();

	/* Perform an MII management read cycle */
	iowrite32be(MIIMCOM_READ_CYCLE, &regs->miimcom);
	/* Dummy read to make sure MIIMCOM is written */
	tmp = ioread32be(&regs->miimcom);
	wmb();

	/* Wait until MII management read is complete */
	/* todo: a timeout could be useful here */
	while ((ioread32be(&regs->miimind)) & MIIMIND_BUSY)
		/* busy wait */;

	/* Read MII management status  */
	*data = (uint16_t)ioread32be(&regs->miimstat);
	wmb();

	iowrite32be(0, &regs->miimcom);
	/* Dummy read to make sure MIIMCOM is written */
	tmp = ioread32be(&regs->miimcom);

	if (*data == 0xffff)
		return -ENXIO;

	return 0;
}