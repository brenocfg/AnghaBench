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
struct vmbus_channel {int /*<<< orphan*/  ch_rxbr; } ;

/* Variables and functions */
 int vmbus_rxbr_empty (int /*<<< orphan*/ *) ; 

bool
vmbus_chan_rx_empty(const struct vmbus_channel *chan)
{

	return (vmbus_rxbr_empty(&chan->ch_rxbr));
}