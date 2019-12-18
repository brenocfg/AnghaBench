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
struct xgbe_prv_data {scalar_t__ channel_count; TYPE_1__* channel; } ;
struct TYPE_2__ {struct TYPE_2__* tx_ring; struct TYPE_2__* rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_AXGBE ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_free_channels(struct xgbe_prv_data *pdata)
{
	if (!pdata->channel)
		return;

	free(pdata->channel->rx_ring, M_AXGBE);
	free(pdata->channel->tx_ring, M_AXGBE);
	free(pdata->channel, M_AXGBE);

	pdata->channel = NULL;
	pdata->channel_count = 0;
}