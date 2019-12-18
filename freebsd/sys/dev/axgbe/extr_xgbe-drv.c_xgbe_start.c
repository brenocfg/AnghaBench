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
struct xgbe_phy_if {int (* phy_start ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* phy_stop ) (struct xgbe_prv_data*) ;} ;
struct xgbe_hw_if {int /*<<< orphan*/  (* exit ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* enable_rx ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* enable_tx ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* init ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {int /*<<< orphan*/  service_work; int /*<<< orphan*/  dev_workqueue; struct xgbe_phy_if phy_if; struct xgbe_hw_if hw_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 
 int stub2 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub3 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub4 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub5 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub6 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgbe_enable_rx_tx_ints (struct xgbe_prv_data*) ; 
 int xgbe_request_irqs (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_start_timers (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_start(struct xgbe_prv_data *pdata)
{
	struct xgbe_hw_if *hw_if = &pdata->hw_if;
	struct xgbe_phy_if *phy_if = &pdata->phy_if;
	int ret;

	DBGPR("-->xgbe_start\n");

	hw_if->init(pdata);

	ret = phy_if->phy_start(pdata);
	if (ret)
		goto err_phy;

	ret = xgbe_request_irqs(pdata);
	if (ret)
		goto err_napi;

	hw_if->enable_tx(pdata);
	hw_if->enable_rx(pdata);

	xgbe_enable_rx_tx_ints(pdata);

	xgbe_start_timers(pdata);
	taskqueue_enqueue(pdata->dev_workqueue, &pdata->service_work);

	DBGPR("<--xgbe_start\n");

	return 0;

err_napi:
	phy_if->phy_stop(pdata);

err_phy:
	hw_if->exit(pdata);

	return ret;
}