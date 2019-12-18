#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  hv_paddr; } ;
struct vmbus_channel {int ch_txflags; TYPE_1__ ch_monprm_dma; int /*<<< orphan*/  ch_montrig_mask; int /*<<< orphan*/  ch_montrig; int /*<<< orphan*/  ch_evtflag_mask; int /*<<< orphan*/  ch_evtflag; } ;

/* Variables and functions */
 int VMBUS_CHAN_TXF_HASMNF ; 
 int /*<<< orphan*/  atomic_set_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set_long (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypercall_signal_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
vmbus_chan_signal_tx(const struct vmbus_channel *chan)
{
	atomic_set_long(chan->ch_evtflag, chan->ch_evtflag_mask);
	if (chan->ch_txflags & VMBUS_CHAN_TXF_HASMNF)
		atomic_set_int(chan->ch_montrig, chan->ch_montrig_mask);
	else
		hypercall_signal_event(chan->ch_monprm_dma.hv_paddr);
}