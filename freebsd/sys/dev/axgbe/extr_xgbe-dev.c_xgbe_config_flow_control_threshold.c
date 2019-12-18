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
struct xgbe_prv_data {unsigned int rx_q_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTL_Q_RQFCR ; 
 int /*<<< orphan*/  RFA ; 
 int /*<<< orphan*/  RFD ; 
 int /*<<< orphan*/  XGMAC_MTL_IOWRITE_BITS (struct xgbe_prv_data*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgbe_config_flow_control_threshold(struct xgbe_prv_data *pdata)
{
	unsigned int i;

	for (i = 0; i < pdata->rx_q_count; i++) {
		/* Activate flow control when less than 4k left in fifo */
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_RQFCR, RFA, 2);

		/* De-activate flow control when more than 6k left in fifo */
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_RQFCR, RFD, 4);
	}
}