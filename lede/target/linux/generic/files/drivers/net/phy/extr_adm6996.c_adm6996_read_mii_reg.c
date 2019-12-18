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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {struct mii_bus* bus; } ;
struct phy_device {TYPE_1__ mdio; } ;
struct mii_bus {int /*<<< orphan*/  (* read ) (struct mii_bus*,int /*<<< orphan*/ ) ;} ;
struct adm6996_priv {struct phy_device* priv; } ;
typedef  enum admreg { ____Placeholder_admreg } admreg ;

/* Variables and functions */
 int /*<<< orphan*/  PHYADDR (int) ; 
 int /*<<< orphan*/  stub1 (struct mii_bus*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16
adm6996_read_mii_reg(struct adm6996_priv *priv, enum admreg reg)
{
	struct phy_device *phydev = priv->priv;
	struct mii_bus *bus = phydev->mdio.bus;

	return bus->read(bus, PHYADDR(reg));
}