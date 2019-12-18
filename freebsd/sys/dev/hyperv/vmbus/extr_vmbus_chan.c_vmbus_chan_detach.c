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
struct vmbus_channel {scalar_t__ ch_refs; int /*<<< orphan*/  ch_detach_task; int /*<<< orphan*/  ch_mgmt_tq; int /*<<< orphan*/  ch_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ VMBUS_CHAN_ISPRIMARY (struct vmbus_channel*) ; 
 int atomic_fetchadd_int (scalar_t__*,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_chan_printf (struct vmbus_channel*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmbus_chan_detach(struct vmbus_channel *chan)
{
	int refs;

	KASSERT(chan->ch_refs > 0, ("chan%u: invalid refcnt %d",
	    chan->ch_id, chan->ch_refs));
	refs = atomic_fetchadd_int(&chan->ch_refs, -1);
#ifdef INVARIANTS
	if (VMBUS_CHAN_ISPRIMARY(chan)) {
		KASSERT(refs == 1, ("chan%u: invalid refcnt %d for prichan",
		    chan->ch_id, refs + 1));
	}
#endif
	if (refs == 1) {
		/*
		 * Detach the target channel.
		 */
		if (bootverbose) {
			vmbus_chan_printf(chan, "chan%u detached\n",
			    chan->ch_id);
		}
		taskqueue_enqueue(chan->ch_mgmt_tq, &chan->ch_detach_task);
	}
}