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
struct xgbe_prv_data {TYPE_1__* netdev; } ;
struct TYPE_2__ {int if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  xgbe_free_rx_data (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_free_tx_data (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_start (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_stop (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_restart_dev(struct xgbe_prv_data *pdata)
{
	DBGPR("-->xgbe_restart_dev\n");

	/* If not running, "restart" will happen on open */
	if ((pdata->netdev->if_drv_flags & IFF_DRV_RUNNING) == 0)
		return;

	xgbe_stop(pdata);

	xgbe_free_tx_data(pdata);
	xgbe_free_rx_data(pdata);

	xgbe_start(pdata);

	DBGPR("<--xgbe_restart_dev\n");
}