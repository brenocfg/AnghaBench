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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct memac_mii_access_mem_map {int dummy; } ;
typedef  enum enet_speed { ____Placeholder_enet_speed } enet_speed ;

/* Variables and functions */
 int EINVAL ; 
 int E_ENET_SPEED_10000 ; 
 int MDIO_CFG_READ_ERR ; 
 int read_phy_reg_10g (struct memac_mii_access_mem_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int read_phy_reg_1g (struct memac_mii_access_mem_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int fman_memac_mii_read_phy_reg(struct memac_mii_access_mem_map *mii_regs,
	uint8_t phy_addr, uint8_t reg, uint16_t *data,
	enum enet_speed enet_speed)
{
	uint32_t ans;
	/* Figure out interface type - 10G vs 1G.
	In 10G interface both phy_addr and devAddr present. */
	if (enet_speed == E_ENET_SPEED_10000)
		ans = read_phy_reg_10g(mii_regs, phy_addr, reg, data);
	else
		ans = read_phy_reg_1g(mii_regs, phy_addr, reg, data);

	if (ans & MDIO_CFG_READ_ERR)
		return -EINVAL;
	return 0;
}