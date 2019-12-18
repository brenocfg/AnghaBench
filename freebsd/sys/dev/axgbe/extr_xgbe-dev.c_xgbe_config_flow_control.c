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
struct xgbe_prv_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_RFCR ; 
 int /*<<< orphan*/  PFCE ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_config_rx_flow_control (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_tx_flow_control (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_config_flow_control(struct xgbe_prv_data *pdata)
{

	xgbe_config_tx_flow_control(pdata);
	xgbe_config_rx_flow_control(pdata);

	XGMAC_IOWRITE_BITS(pdata, MAC_RFCR, PFCE, 0);
}