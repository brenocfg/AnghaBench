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
struct vmbus_xact {int dummy; } ;
struct vmbus_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 scalar_t__ vmbus_chan_is_revoked (struct vmbus_channel const*) ; 
 int /*<<< orphan*/  vmbus_chan_rx_empty (struct vmbus_channel const*) ; 
 void* vmbus_xact_busywait (struct vmbus_xact*,size_t*) ; 
 void* vmbus_xact_wait (struct vmbus_xact*,size_t*) ; 

const void *
vmbus_chan_xact_wait(const struct vmbus_channel *chan,
    struct vmbus_xact *xact, size_t *resp_len, bool can_sleep)
{
	const void *ret;

	if (can_sleep)
		ret = vmbus_xact_wait(xact, resp_len);
	else
		ret = vmbus_xact_busywait(xact, resp_len);
	if (vmbus_chan_is_revoked(chan)) {
		/*
		 * This xact probably is interrupted, and the
		 * interruption can race the reply reception,
		 * so we have to make sure that there are nothing
		 * left on the RX bufring, i.e. this xact will
		 * not be touched, once this function returns.
		 *
		 * Since the hypervisor will not put more data
		 * onto the RX bufring once the channel is revoked,
		 * the following loop will be terminated, once all
		 * data are drained by the driver's channel
		 * callback.
		 */
		while (!vmbus_chan_rx_empty(chan)) {
			if (can_sleep)
				pause("chxact", 1);
			else
				DELAY(1000);
		}
	}
	return (ret);
}