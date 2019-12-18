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
struct vmbus_channel {int ch_subchan_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMBUS_CHAN_ISPRIMARY (struct vmbus_channel*) ; 
 int /*<<< orphan*/  vmbus_chan_close_internal (struct vmbus_channel*) ; 
 int /*<<< orphan*/  vmbus_chan_detach (struct vmbus_channel*) ; 
 struct vmbus_channel** vmbus_subchan_get (struct vmbus_channel*,int) ; 
 int /*<<< orphan*/  vmbus_subchan_rel (struct vmbus_channel**,int) ; 

void
vmbus_chan_close(struct vmbus_channel *chan)
{
	int subchan_cnt;

	if (!VMBUS_CHAN_ISPRIMARY(chan)) {
		/*
		 * Sub-channel is closed when its primary channel
		 * is closed; done.
		 */
		return;
	}

	/*
	 * Close all sub-channels, if any.
	 */
	subchan_cnt = chan->ch_subchan_cnt;
	if (subchan_cnt > 0) {
		struct vmbus_channel **subchan;
		int i;

		subchan = vmbus_subchan_get(chan, subchan_cnt);
		for (i = 0; i < subchan_cnt; ++i) {
			vmbus_chan_close_internal(subchan[i]);
			/*
			 * This sub-channel is referenced, when it is
			 * linked to the primary channel; drop that
			 * reference now.
			 */
			vmbus_chan_detach(subchan[i]);
		}
		vmbus_subchan_rel(subchan, subchan_cnt);
	}

	/* Then close the primary channel. */
	vmbus_chan_close_internal(chan);
}