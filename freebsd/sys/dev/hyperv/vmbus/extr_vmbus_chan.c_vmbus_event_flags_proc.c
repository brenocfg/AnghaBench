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
typedef  int uint32_t ;
typedef  scalar_t__ u_long ;
struct vmbus_softc {struct vmbus_channel** vmbus_chmap; } ;
struct vmbus_channel {int ch_flags; int /*<<< orphan*/  ch_task; int /*<<< orphan*/  ch_tq; int /*<<< orphan*/  ch_rxbr; } ;

/* Variables and functions */
 int VMBUS_CHAN_FLAG_BATCHREAD ; 
 int VMBUS_EVTFLAG_SHIFT ; 
 int /*<<< orphan*/  __compiler_membar () ; 
 scalar_t__ __predict_false (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_swap_long (scalar_t__ volatile*,int /*<<< orphan*/ ) ; 
 int ffsl (scalar_t__) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_rxbr_intr_mask (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline void
vmbus_event_flags_proc(struct vmbus_softc *sc, volatile u_long *event_flags,
    int flag_cnt)
{
	int f;

	for (f = 0; f < flag_cnt; ++f) {
		uint32_t chid_base;
		u_long flags;
		int chid_ofs;

		if (event_flags[f] == 0)
			continue;

		flags = atomic_swap_long(&event_flags[f], 0);
		chid_base = f << VMBUS_EVTFLAG_SHIFT;

		while ((chid_ofs = ffsl(flags)) != 0) {
			struct vmbus_channel *chan;

			--chid_ofs; /* NOTE: ffsl is 1-based */
			flags &= ~(1UL << chid_ofs);

			chan = sc->vmbus_chmap[chid_base + chid_ofs];
			if (__predict_false(chan == NULL)) {
				/* Channel is closed. */
				continue;
			}
			__compiler_membar();

			if (chan->ch_flags & VMBUS_CHAN_FLAG_BATCHREAD)
				vmbus_rxbr_intr_mask(&chan->ch_rxbr);
			taskqueue_enqueue(chan->ch_tq, &chan->ch_task);
		}
	}
}