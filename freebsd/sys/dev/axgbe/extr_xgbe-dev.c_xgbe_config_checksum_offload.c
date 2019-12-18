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
struct xgbe_prv_data {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int IFCAP_RXCSUM ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_disable_rx_csum (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_enable_rx_csum (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_config_checksum_offload(struct xgbe_prv_data *pdata)
{
	if ((if_getcapenable(pdata->netdev) & IFCAP_RXCSUM) != 0)
		xgbe_enable_rx_csum(pdata);
	else
		xgbe_disable_rx_csum(pdata);
}