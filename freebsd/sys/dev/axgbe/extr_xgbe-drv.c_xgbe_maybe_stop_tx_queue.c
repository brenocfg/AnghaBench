#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ xmit_more; } ;
struct xgbe_ring {TYPE_1__ tx; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* tx_start_xmit ) (struct xgbe_channel*,struct xgbe_ring*) ;} ;
struct xgbe_prv_data {TYPE_2__ hw_if; } ;
struct xgbe_channel {struct xgbe_prv_data* pdata; } ;

/* Variables and functions */
 int EFBIG ; 
 int /*<<< orphan*/  stub1 (struct xgbe_channel*,struct xgbe_ring*) ; 
 unsigned int xgbe_tx_avail_desc (struct xgbe_ring*) ; 

__attribute__((used)) static int xgbe_maybe_stop_tx_queue(struct xgbe_channel *channel,
				    struct xgbe_ring *ring, unsigned int count)
{
	struct xgbe_prv_data *pdata = channel->pdata;

	if (count > xgbe_tx_avail_desc(ring)) {
		/* If we haven't notified the hardware because of xmit_more
		 * support, tell it now
		 */
		if (ring->tx.xmit_more)
			pdata->hw_if.tx_start_xmit(channel, ring);

		return EFBIG;
	}

	return 0;
}