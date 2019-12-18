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

/* Variables and functions */
 unsigned long ADDR_SHIFT ; 
 unsigned long DATA_SHIFT ; 
 int /*<<< orphan*/  PCIEPHY0_CFG ; 
 unsigned long WRITE_MODE ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pcie_w32 (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_pciephy_busy () ; 

__attribute__((used)) static void pcie_phy(unsigned long addr, unsigned long val)
{
	wait_pciephy_busy();
	pcie_w32(WRITE_MODE | (val << DATA_SHIFT) | (addr << ADDR_SHIFT),
		 PCIEPHY0_CFG);
	mdelay(1);
	wait_pciephy_busy();
}