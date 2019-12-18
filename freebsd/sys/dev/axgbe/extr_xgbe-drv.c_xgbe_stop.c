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
struct xgbe_phy_if {int /*<<< orphan*/  (* phy_stop ) (struct xgbe_prv_data*) ;} ;
struct xgbe_hw_if {int /*<<< orphan*/  (* exit ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* disable_rx ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* disable_tx ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {int /*<<< orphan*/  dev_workqueue; struct xgbe_phy_if phy_if; struct xgbe_hw_if hw_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub2 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub3 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub4 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  taskqueue_drain_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_free_irqs (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_stop_timers (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_stop(struct xgbe_prv_data *pdata)
{
	struct xgbe_hw_if *hw_if = &pdata->hw_if;
	struct xgbe_phy_if *phy_if = &pdata->phy_if;

	DBGPR("-->xgbe_stop\n");

	xgbe_stop_timers(pdata);
	taskqueue_drain_all(pdata->dev_workqueue);

	hw_if->disable_tx(pdata);
	hw_if->disable_rx(pdata);

	xgbe_free_irqs(pdata);

	phy_if->phy_stop(pdata);

	hw_if->exit(pdata);

	DBGPR("<--xgbe_stop\n");
}