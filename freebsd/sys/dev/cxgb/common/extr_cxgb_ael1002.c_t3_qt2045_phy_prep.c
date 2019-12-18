#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mdio_ops {int dummy; } ;
struct cphy {int addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  adapter; struct cphy phy; } ;
typedef  TYPE_1__ pinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_DEV_PMA_PMD ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_AUI ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  cphy_init (struct cphy*,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,struct mdio_ops const*,int,char*) ; 
 int /*<<< orphan*/  mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  qt2045_ops ; 

int t3_qt2045_phy_prep(pinfo_t *pinfo, int phy_addr,
		       const struct mdio_ops *mdio_ops)
{
	unsigned int stat;
	struct cphy *phy = &pinfo->phy;

	cphy_init(phy, pinfo->adapter, pinfo, phy_addr, &qt2045_ops, mdio_ops,
		  SUPPORTED_10000baseT_Full | SUPPORTED_AUI | SUPPORTED_TP,
		  "10GBASE-CX4");

	/*
	 * Some cards where the PHY is supposed to be at address 0 actually
	 * have it at 1.
	 */
	if (!phy_addr && !mdio_read(phy, MDIO_DEV_PMA_PMD, MII_BMSR, &stat) &&
	    stat == 0xffff)
		phy->addr = 1;
	return 0;
}