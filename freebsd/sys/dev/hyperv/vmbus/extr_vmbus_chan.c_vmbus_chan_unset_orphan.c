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
struct vmbus_channel {int /*<<< orphan*/  ch_orphan_lock; int /*<<< orphan*/ * ch_orphan_xact; } ;

/* Variables and functions */
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

void
vmbus_chan_unset_orphan(struct vmbus_channel *chan)
{

	sx_xlock(&chan->ch_orphan_lock);
	chan->ch_orphan_xact = NULL;
	sx_xunlock(&chan->ch_orphan_lock);
}