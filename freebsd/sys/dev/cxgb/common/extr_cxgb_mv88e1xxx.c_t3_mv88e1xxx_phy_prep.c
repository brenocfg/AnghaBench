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
struct cphy {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  adapter; struct cphy phy; } ;
typedef  TYPE_1__ pinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E1XXX_EXTENDED_ADDR ; 
 int /*<<< orphan*/  MV88E1XXX_EXTENDED_DATA ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_IRQ ; 
 int SUPPORTED_MII ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  cphy_init (struct cphy*,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,struct mdio_ops const*,int,char*) ; 
 int mdio_write (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mv88e1xxx_downshift_set (struct cphy*,int) ; 
 int /*<<< orphan*/  mv88e1xxx_ops ; 

int t3_mv88e1xxx_phy_prep(pinfo_t *pinfo, int phy_addr,
			  const struct mdio_ops *mdio_ops)
{
	struct cphy *phy = &pinfo->phy;
	int err;

	cphy_init(phy, pinfo->adapter, pinfo, phy_addr, &mv88e1xxx_ops, mdio_ops,
		  SUPPORTED_10baseT_Full | SUPPORTED_100baseT_Full |
		  SUPPORTED_1000baseT_Full | SUPPORTED_Autoneg | SUPPORTED_MII |
		  SUPPORTED_TP | SUPPORTED_IRQ, "10/100/1000BASE-T");

	/* Configure copper PHY transmitter as class A to reduce EMI. */
	err = mdio_write(phy, 0, MV88E1XXX_EXTENDED_ADDR, 0xb);
	if (!err)
		err = mdio_write(phy, 0, MV88E1XXX_EXTENDED_DATA, 0x8004);

	if (!err)
		err = mv88e1xxx_downshift_set(phy, 1);   /* Enable downshift */
	return err;
}