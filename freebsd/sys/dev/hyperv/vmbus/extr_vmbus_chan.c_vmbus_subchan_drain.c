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
struct vmbus_channel {scalar_t__ ch_subchan_cnt; int /*<<< orphan*/  ch_subchan_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_sleep (struct vmbus_channel*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
vmbus_subchan_drain(struct vmbus_channel *pri_chan)
{
	mtx_lock(&pri_chan->ch_subchan_lock);
	while (pri_chan->ch_subchan_cnt > 0)
		mtx_sleep(pri_chan, &pri_chan->ch_subchan_lock, 0, "dsubch", 0);
	mtx_unlock(&pri_chan->ch_subchan_lock);
}