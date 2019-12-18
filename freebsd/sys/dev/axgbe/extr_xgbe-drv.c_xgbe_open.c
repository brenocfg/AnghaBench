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
struct xgbe_desc_if {int (* alloc_ring_resources ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* free_ring_resources ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {int rx_buf_size; int /*<<< orphan*/  dev_state; int /*<<< orphan*/  restart_work; int /*<<< orphan*/  service_work; struct xgbe_desc_if desc_if; } ;
struct ifnet {struct xgbe_prv_data* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  XGBE_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_getmtu (struct ifnet*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub2 (struct xgbe_prv_data*) ; 
 int xgbe_alloc_channels (struct xgbe_prv_data*) ; 
 int xgbe_calc_rx_buf_size (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_free_channels (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_init_timers (struct xgbe_prv_data*) ; 
 int xgbe_phy_init (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_restart ; 
 int /*<<< orphan*/  xgbe_service ; 
 int xgbe_start (struct xgbe_prv_data*) ; 

int xgbe_open(struct ifnet *netdev)
{
	struct xgbe_prv_data *pdata = netdev->if_softc;
	struct xgbe_desc_if *desc_if = &pdata->desc_if;
	int ret;

	DBGPR("-->xgbe_open\n");

	/* Initialize the phy */
	ret = xgbe_phy_init(pdata);
	if (ret)
		return ret;

	/* Calculate the Rx buffer size before allocating rings */
	ret = xgbe_calc_rx_buf_size(netdev, if_getmtu(netdev));
	if (ret < 0) {
		goto err_ptpclk;
	}
	pdata->rx_buf_size = ret;

	/* Allocate the channel and ring structures */
	ret = xgbe_alloc_channels(pdata);
	if (ret) {
		printf("xgbe_alloc_channels failed\n");
		goto err_ptpclk;
	}

	/* Allocate the ring descriptors and buffers */
	ret = desc_if->alloc_ring_resources(pdata);
	if (ret) {
		printf("desc_if->alloc_ring_resources failed\n");
		goto err_channels;
	}

	TASK_INIT(&pdata->service_work, 0, xgbe_service, pdata);
	TASK_INIT(&pdata->restart_work, 0, xgbe_restart, pdata);
	xgbe_init_timers(pdata);

	ret = xgbe_start(pdata);
	if (ret)
		goto err_rings;

	clear_bit(XGBE_DOWN, &pdata->dev_state);

	DBGPR("<--xgbe_open\n");

	return 0;

err_rings:
	desc_if->free_ring_resources(pdata);

err_channels:
	xgbe_free_channels(pdata);

err_ptpclk:

	return ret;
}