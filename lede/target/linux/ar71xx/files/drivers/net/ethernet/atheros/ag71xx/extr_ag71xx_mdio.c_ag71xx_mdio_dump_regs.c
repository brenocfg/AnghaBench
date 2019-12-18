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
struct ag71xx_mdio {TYPE_1__* mii_bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_MII_ADDR ; 
 int /*<<< orphan*/  AG71XX_REG_MII_CFG ; 
 int /*<<< orphan*/  AG71XX_REG_MII_CMD ; 
 int /*<<< orphan*/  AG71XX_REG_MII_CTRL ; 
 int /*<<< orphan*/  AG71XX_REG_MII_IND ; 
 int /*<<< orphan*/  AG71XX_REG_MII_STATUS ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ag71xx_mdio_rr (struct ag71xx_mdio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ag71xx_mdio_dump_regs(struct ag71xx_mdio *am)
{
	DBG("%s: mii_cfg=%08x, mii_cmd=%08x, mii_addr=%08x\n",
		am->mii_bus->name,
		ag71xx_mdio_rr(am, AG71XX_REG_MII_CFG),
		ag71xx_mdio_rr(am, AG71XX_REG_MII_CMD),
		ag71xx_mdio_rr(am, AG71XX_REG_MII_ADDR));
	DBG("%s: mii_ctrl=%08x, mii_status=%08x, mii_ind=%08x\n",
		am->mii_bus->name,
		ag71xx_mdio_rr(am, AG71XX_REG_MII_CTRL),
		ag71xx_mdio_rr(am, AG71XX_REG_MII_STATUS),
		ag71xx_mdio_rr(am, AG71XX_REG_MII_IND));
}