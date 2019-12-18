#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {size_t phy_devs; scalar_t__ phy_base; } ;

/* Variables and functions */
 scalar_t__ CPHY_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPHY_MAP (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cphy_lock ; 
 TYPE_1__* port_data ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u32 __combo_phy_reg_read(u8 sata_port, u32 addr)
{
	u32 data;
	u8 dev = port_data[sata_port].phy_devs;
	spin_lock(&cphy_lock);
	writel(CPHY_MAP(dev, addr), port_data[sata_port].phy_base + 0x800);
	data = readl(port_data[sata_port].phy_base + CPHY_ADDR(addr));
	spin_unlock(&cphy_lock);
	return data;
}