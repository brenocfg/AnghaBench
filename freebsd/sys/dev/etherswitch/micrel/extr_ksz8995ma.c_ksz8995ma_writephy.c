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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BMCR_PDOWN ; 
 int BMCR_STARTNEG ; 
 scalar_t__ KSZ8995MA_PC12_BASE ; 
 scalar_t__ KSZ8995MA_PC13_BASE ; 
 int KSZ8995MA_PDOWN ; 
 int KSZ8995MA_PORT_SIZE ; 
 int KSZ8995MA_STARTNEG ; 
 int MII_ANAR ; 
 int MII_BMCR ; 
 int ksz8995ma_readreg (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ksz8995ma_writereg (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int
ksz8995ma_writephy(device_t dev, int phy, int reg, int data)
{
int portreg;

	/* 
	 * This is no mdio/mdc connection code.
         * simulate MIIM Registers via the SPI interface
	 */
	if (reg == MII_BMCR) {
		portreg = ksz8995ma_readreg(dev, KSZ8995MA_PC13_BASE + 
			KSZ8995MA_PORT_SIZE * phy);
		if (data & BMCR_PDOWN)
			portreg |= KSZ8995MA_PDOWN;
		else
			portreg &= ~KSZ8995MA_PDOWN;
		if (data & BMCR_STARTNEG)
			portreg |= KSZ8995MA_STARTNEG;
		else
			portreg &= ~KSZ8995MA_STARTNEG;
		ksz8995ma_writereg(dev, KSZ8995MA_PC13_BASE + 
			KSZ8995MA_PORT_SIZE * phy, portreg);
	} else if (reg == MII_ANAR) {
		portreg = ksz8995ma_readreg(dev, KSZ8995MA_PC12_BASE + 
			KSZ8995MA_PORT_SIZE * phy);
		portreg &= 0xf;
		portreg |= ((data >> 5) & 0x0f);
		ksz8995ma_writereg(dev, KSZ8995MA_PC12_BASE + 
			KSZ8995MA_PORT_SIZE * phy, portreg);
	}
	return (0);
}