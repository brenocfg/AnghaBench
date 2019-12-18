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
struct vmbus_channel {int /*<<< orphan*/  ch_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMBUS_CHAN_FLAG_BATCHREAD ; 

void
vmbus_chan_set_readbatch(struct vmbus_channel *chan, bool on)
{
	if (!on)
		chan->ch_flags &= ~VMBUS_CHAN_FLAG_BATCHREAD;
	else
		chan->ch_flags |= VMBUS_CHAN_FLAG_BATCHREAD;
}