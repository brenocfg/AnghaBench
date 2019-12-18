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
struct xgbe_desc_if {int /*<<< orphan*/  (* free_ring_resources ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {int /*<<< orphan*/  dev_state; struct xgbe_desc_if desc_if; } ;
struct ifnet {struct xgbe_prv_data* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int /*<<< orphan*/  XGBE_DOWN ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_free_channels (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_stop (struct xgbe_prv_data*) ; 

int xgbe_close(struct ifnet *netdev)
{
	struct xgbe_prv_data *pdata = netdev->if_softc;
	struct xgbe_desc_if *desc_if = &pdata->desc_if;

	DBGPR("-->xgbe_close\n");

	/* Stop the device */
	xgbe_stop(pdata);

	/* Free the ring descriptors and buffers */
	desc_if->free_ring_resources(pdata);

	/* Free the channel and ring structures */
	xgbe_free_channels(pdata);

	set_bit(XGBE_DOWN, &pdata->dev_state);

	DBGPR("<--xgbe_close\n");

	return 0;
}