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
struct vmbus_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmbus_chan_cpu_set (struct vmbus_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmbus_chan_cpu_default(struct vmbus_channel *chan)
{
	/*
	 * By default, pin the channel to cpu0.  Devices having
	 * special channel-cpu mapping requirement should call
	 * vmbus_chan_cpu_{set,rr}().
	 */
	vmbus_chan_cpu_set(chan, 0);
}