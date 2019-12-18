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
struct ifnet {scalar_t__ if_softc; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_id; } ;
typedef  TYPE_1__ cvm_oct_private_t ;

/* Variables and functions */
 int MV88E61XX_SMI_CMD_22 ; 
 int MV88E61XX_SMI_CMD_BUSY ; 
 int MV88E61XX_SMI_CMD_PHY (int) ; 
 int MV88E61XX_SMI_CMD_READ ; 
 int MV88E61XX_SMI_CMD_REG (int) ; 
 int /*<<< orphan*/  MV88E61XX_SMI_REG_CMD ; 
 int /*<<< orphan*/  MV88E61XX_SMI_REG_DAT ; 
 int cvm_oct_mdio_read (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvm_oct_mdio_write (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int cvm_oct_mv88e61xx_smi_wait (struct ifnet*) ; 

__attribute__((used)) static int
cvm_oct_mv88e61xx_smi_read(struct ifnet *ifp, int phy_id, int location)
{
	cvm_oct_private_t *priv = (cvm_oct_private_t *)ifp->if_softc;
	int error;

	error = cvm_oct_mv88e61xx_smi_wait(ifp);
	if (error != 0)
		return (0);

	cvm_oct_mdio_write(ifp, priv->phy_id, MV88E61XX_SMI_REG_CMD,
	    MV88E61XX_SMI_CMD_BUSY | MV88E61XX_SMI_CMD_22 |
	    MV88E61XX_SMI_CMD_READ | MV88E61XX_SMI_CMD_PHY(phy_id) |
	    MV88E61XX_SMI_CMD_REG(location));

	error = cvm_oct_mv88e61xx_smi_wait(ifp);
	if (error != 0)
		return (0);

	return (cvm_oct_mdio_read(ifp, priv->phy_id, MV88E61XX_SMI_REG_DAT));
}