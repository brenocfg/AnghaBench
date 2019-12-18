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
typedef  int uint16_t ;
struct ifnet {scalar_t__ if_softc; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_id; } ;
typedef  TYPE_1__ cvm_oct_private_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int MV88E61XX_SMI_CMD_BUSY ; 
 int /*<<< orphan*/  MV88E61XX_SMI_REG_CMD ; 
 int cvm_oct_mdio_read (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cvm_oct_mv88e61xx_smi_wait(struct ifnet *ifp)
{
	cvm_oct_private_t *priv = (cvm_oct_private_t *)ifp->if_softc;
	uint16_t cmd;
	unsigned i;

	for (i = 0; i < 10000; i++) {
		cmd = cvm_oct_mdio_read(ifp, priv->phy_id, MV88E61XX_SMI_REG_CMD);
		if ((cmd & MV88E61XX_SMI_CMD_BUSY) == 0)
			return (0);
	}
	return (ETIMEDOUT);
}