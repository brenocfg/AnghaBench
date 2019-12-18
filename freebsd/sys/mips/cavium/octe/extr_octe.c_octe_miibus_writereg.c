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
struct TYPE_3__ {int phy_id; int /*<<< orphan*/  ifp; int /*<<< orphan*/  (* mdio_write ) (int /*<<< orphan*/ ,int,int,int) ;} ;
typedef  TYPE_1__ cvm_oct_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  cvm_oct_mdio_write (int /*<<< orphan*/ ,int,int,int) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
octe_miibus_writereg(device_t dev, int phy, int reg, int val)
{
	cvm_oct_private_t *priv;

	priv = device_get_softc(dev);

	/*
	 * Try interface-specific MII routine.
	 */
	if (priv->mdio_write != NULL) {
		priv->mdio_write(priv->ifp, phy, reg, val);
		return (0);
	}

	/*
	 * Try generic MII routine.
	 */
	KASSERT(phy == priv->phy_id,
	    ("write to phy %u but our phy is %u", phy, priv->phy_id));
	cvm_oct_mdio_write(priv->ifp, phy, reg, val);

	return (0);
}