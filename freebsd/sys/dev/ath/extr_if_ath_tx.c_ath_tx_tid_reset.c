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
struct ath_tid {scalar_t__ paused; scalar_t__ sched; scalar_t__ addba_tx_pending; scalar_t__ isfiltered; scalar_t__ bar_tx; scalar_t__ bar_wait; scalar_t__ cleanup_inprogress; scalar_t__ incomp; } ;
struct ath_softc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
ath_tx_tid_reset(struct ath_softc *sc, struct ath_tid *tid)
{

#if 0
	tid->bar_wait = tid->bar_tx = tid->isfiltered = 0;
	tid->paused = tid->sched = tid->addba_tx_pending = 0;
	tid->incomp = tid->cleanup_inprogress = 0;
#endif

	/*
	 * If we have a bar_wait set, we need to unpause the TID
	 * here.  Otherwise once cleanup has finished, the TID won't
	 * have the right paused counter.
	 *
	 * XXX I'm not going through resume here - I don't want the
	 * node to be rescheuled just yet.  This however should be
	 * methodized!
	 */
	if (tid->bar_wait) {
		if (tid->paused > 0) {
			tid->paused --;
		}
	}

	/*
	 * XXX same with a currently filtered TID.
	 *
	 * Since this is being called during a flush, we assume that
	 * the filtered frame list is actually empty.
	 *
	 * XXX TODO: add in a check to ensure that the filtered queue
	 * depth is actually 0!
	 */
	if (tid->isfiltered) {
		if (tid->paused > 0) {
			tid->paused --;
		}
	}

	/*
	 * Clear BAR, filtered frames, scheduled and ADDBA pending.
	 * The TID may be going through cleanup from the last association
	 * where things in the BAW are still in the hardware queue.
	 */
	tid->bar_wait = 0;
	tid->bar_tx = 0;
	tid->isfiltered = 0;
	tid->sched = 0;
	tid->addba_tx_pending = 0;

	/*
	 * XXX TODO: it may just be enough to walk the HWQs and mark
	 * frames for that node as non-aggregate; or mark the ath_node
	 * with something that indicates that aggregation is no longer
	 * occurring.  Then we can just toss the BAW complaints and
	 * do a complete hard reset of state here - no pause, no
	 * complete counter, etc.
	 */

}