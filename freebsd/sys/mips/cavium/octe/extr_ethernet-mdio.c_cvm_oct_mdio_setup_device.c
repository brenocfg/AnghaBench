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
struct TYPE_2__ {int /*<<< orphan*/ * mdio_write; int /*<<< orphan*/ * mdio_read; int /*<<< orphan*/ * phy_device; int /*<<< orphan*/  port; int /*<<< orphan*/  phy_id; } ;
typedef  TYPE_1__ cvm_oct_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  cvmx_helper_board_get_mii_address (int /*<<< orphan*/ ) ; 

int cvm_oct_mdio_setup_device(struct ifnet *ifp)
{
	cvm_oct_private_t *priv = (cvm_oct_private_t *)ifp->if_softc;

	priv->phy_id = cvmx_helper_board_get_mii_address(priv->port);
	priv->phy_device = NULL;
	priv->mdio_read = NULL;
	priv->mdio_write = NULL;

	return 0;
}