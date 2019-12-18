#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct al_hal_eth_adapter {TYPE_2__* mac_regs_base; } ;
struct TYPE_3__ {int /*<<< orphan*/  phy_regs_base; } ;
struct TYPE_4__ {TYPE_1__ mac_1g; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int al_eth_mdio_1g_mac_write(struct al_hal_eth_adapter *adapter,
			     uint32_t phy_addr __attribute__((__unused__)),
			     uint32_t reg, uint16_t val)
{
	al_reg_write32(
		&adapter->mac_regs_base->mac_1g.phy_regs_base + reg, val);
	return 0;
}