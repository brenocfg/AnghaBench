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
struct vmbus_channel {int ch_flags; int /*<<< orphan*/  ch_id; } ;
struct task {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  TASK_INIT (struct task*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmbus_channel*) ; 
 int VMBUS_CHAN_FLAG_BATCHREAD ; 
 int /*<<< orphan*/  vmbus_chan_polldis_task ; 
 int /*<<< orphan*/  vmbus_chan_run_task (struct vmbus_channel*,struct task*) ; 

void
vmbus_chan_poll_disable(struct vmbus_channel *chan)
{
	struct task poll_dis;

	KASSERT(chan->ch_flags & VMBUS_CHAN_FLAG_BATCHREAD,
	    ("disable polling on non-batch chan%u", chan->ch_id));

	TASK_INIT(&poll_dis, 0, vmbus_chan_polldis_task, chan);
	vmbus_chan_run_task(chan, &poll_dis);
}