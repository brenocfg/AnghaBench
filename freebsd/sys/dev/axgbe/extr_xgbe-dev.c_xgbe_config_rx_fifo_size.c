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
struct TYPE_2__ {int /*<<< orphan*/  rx_fifo_size; } ;
struct xgbe_prv_data {unsigned int rx_q_count; TYPE_1__ hw_feat; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTL_Q_RQOMR ; 
 int /*<<< orphan*/  RQS ; 
 int /*<<< orphan*/  XGMAC_MTL_IOWRITE_BITS (struct xgbe_prv_data*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int xgbe_calculate_per_queue_fifo (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void xgbe_config_rx_fifo_size(struct xgbe_prv_data *pdata)
{
	unsigned int fifo_size;
	unsigned int i;

	fifo_size = xgbe_calculate_per_queue_fifo(pdata->hw_feat.rx_fifo_size,
						  pdata->rx_q_count);

	for (i = 0; i < pdata->rx_q_count; i++)
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_RQOMR, RQS, fifo_size);
}