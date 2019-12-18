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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_WRITEREG (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MII_ATH_MMD_ADDR ; 
 int /*<<< orphan*/  MII_ATH_MMD_DATA ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

void
arswitch_writemmd(device_t dev, int phy, uint16_t dbg_addr,
    uint16_t dbg_data)
{
	(void) MDIO_WRITEREG(device_get_parent(dev), phy,
	    MII_ATH_MMD_ADDR, dbg_addr);
	(void) MDIO_WRITEREG(device_get_parent(dev), phy,
	    MII_ATH_MMD_DATA, dbg_data);
}