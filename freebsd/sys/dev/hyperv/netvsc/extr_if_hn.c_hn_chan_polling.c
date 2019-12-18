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
typedef  int /*<<< orphan*/  u_int ;
struct vmbus_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmbus_chan_poll_disable (struct vmbus_channel*) ; 
 int /*<<< orphan*/  vmbus_chan_poll_enable (struct vmbus_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hn_chan_polling(struct vmbus_channel *chan, u_int pollhz)
{
	if (pollhz == 0)
		vmbus_chan_poll_disable(chan);
	else
		vmbus_chan_poll_enable(chan, pollhz);
}