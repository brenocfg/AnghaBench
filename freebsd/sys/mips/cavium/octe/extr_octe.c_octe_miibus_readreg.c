#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int (* mdio_read ) (int /*<<< orphan*/ ,int,int) ;int phy_id; int /*<<< orphan*/  ifp; } ;
typedef  TYPE_1__ cvm_oct_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int cvm_oct_mdio_read (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
octe_miibus_readreg(device_t dev, int phy, int reg)
{
	cvm_oct_private_t *priv;

	priv = device_get_softc(dev);

	/*
	 * Try interface-specific MII routine.
	 */
	if (priv->mdio_read != NULL)
		return (priv->mdio_read(priv->ifp, phy, reg));

	/*
	 * Try generic MII routine.
	 */
	KASSERT(phy == priv->phy_id,
	    ("read from phy %u but our phy is %u", phy, priv->phy_id));
	return (cvm_oct_mdio_read(priv->ifp, phy, reg));
}