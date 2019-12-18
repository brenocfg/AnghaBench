#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xgbe_prv_data {int rx_buf_size; } ;
struct ifnet {int if_mtu; struct xgbe_prv_data* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int xgbe_calc_rx_buf_size (struct ifnet*,int) ; 
 int /*<<< orphan*/  xgbe_restart_dev (struct xgbe_prv_data*) ; 

int xgbe_change_mtu(struct ifnet *netdev, int mtu)
{
	struct xgbe_prv_data *pdata = netdev->if_softc;
	int ret;

	DBGPR("-->xgbe_change_mtu\n");

	ret = xgbe_calc_rx_buf_size(netdev, mtu);
	if (ret < 0)
		return -ret;

	pdata->rx_buf_size = ret;
	netdev->if_mtu = mtu;

	xgbe_restart_dev(pdata);

	DBGPR("<--xgbe_change_mtu\n");

	return 0;
}