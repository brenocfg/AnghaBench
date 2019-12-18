#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ifnet {int /*<<< orphan*/  if_mtu; scalar_t__ if_softc; } ;
struct TYPE_3__ {int phy_id; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ cvm_oct_private_t ;
struct TYPE_4__ {int board_type; } ;

/* Variables and functions */
#define  CVMX_BOARD_TYPE_CUST_LANNER_MR320 129 
#define  CVMX_BOARD_TYPE_CUST_LANNER_MR321X 128 
 int ENXIO ; 
 int /*<<< orphan*/  ETHERMTU ; 
 scalar_t__ cvm_assign_mac_address (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvm_oct_common_change_mtu (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvm_oct_common_set_mac_address (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvm_oct_mdio_setup_device (struct ifnet*) ; 
 int /*<<< orphan*/  cvm_oct_mv88e61xx_setup_device (struct ifnet*) ; 
 TYPE_2__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  device_attach (int /*<<< orphan*/ ) ; 

int cvm_oct_common_init(struct ifnet *ifp)
{
	uint8_t mac[6];
	cvm_oct_private_t *priv = (cvm_oct_private_t *)ifp->if_softc;

	if (cvm_assign_mac_address(NULL, mac) != 0)
		return ENXIO;

	ifp->if_mtu = ETHERMTU;

	cvm_oct_mdio_setup_device(ifp);

	cvm_oct_common_set_mac_address(ifp, mac);
	cvm_oct_common_change_mtu(ifp, ifp->if_mtu);

	/*
	 * Do any last-minute board-specific initialization.
	 */
	switch (cvmx_sysinfo_get()->board_type) {
#if defined(OCTEON_VENDOR_LANNER)
	case CVMX_BOARD_TYPE_CUST_LANNER_MR320:
	case CVMX_BOARD_TYPE_CUST_LANNER_MR321X:
		if (priv->phy_id == 16)
			cvm_oct_mv88e61xx_setup_device(ifp);
		break;
#endif
	default:
		break;
	}

	device_attach(priv->dev);

	return 0;
}