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
 unsigned short CR_READ_ENABLE ; 
 int /*<<< orphan*/  SATA_PHY_ASIC_DATA ; 
 int /*<<< orphan*/  SATA_PHY_ASIC_STAT ; 
 unsigned short readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_cr_ack () ; 
 int /*<<< orphan*/  writel (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned short read_cr(unsigned short address)
{
	writel(address, SATA_PHY_ASIC_STAT);
	wait_cr_ack();
	writel(CR_READ_ENABLE, SATA_PHY_ASIC_DATA);
	wait_cr_ack();
	return readl(SATA_PHY_ASIC_STAT);
}