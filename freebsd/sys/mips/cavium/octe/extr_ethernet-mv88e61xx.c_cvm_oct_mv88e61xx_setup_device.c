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
struct TYPE_2__ {char* phy_device; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; } ;
typedef  TYPE_1__ cvm_oct_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  cvm_oct_mv88e61xx_smi_read ; 
 int /*<<< orphan*/  cvm_oct_mv88e61xx_smi_write ; 

int
cvm_oct_mv88e61xx_setup_device(struct ifnet *ifp)
{
	cvm_oct_private_t *priv = (cvm_oct_private_t *)ifp->if_softc;

	priv->mdio_read = cvm_oct_mv88e61xx_smi_read;
	priv->mdio_write = cvm_oct_mv88e61xx_smi_write;
	priv->phy_device = "mv88e61xxphy";

	return (0);
}