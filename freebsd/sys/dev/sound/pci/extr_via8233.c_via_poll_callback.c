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
typedef  int uint32_t ;
struct via_info {scalar_t__ polling; TYPE_1__* rch; TYPE_1__* pch; int /*<<< orphan*/  lock; int /*<<< orphan*/  poll_timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int NDXSCHANS ; 
 int NMSGDCHANS ; 
 int NWRCHANS ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct via_info*) ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 scalar_t__ via_chan_active (struct via_info*) ; 
 scalar_t__ via_poll_channel (TYPE_1__*) ; 

__attribute__((used)) static void
via_poll_callback(void *arg)
{
	struct via_info *via = arg;
	uint32_t ptrigger = 0, rtrigger = 0;
	int i;

	if (via == NULL)
		return;

	snd_mtxlock(via->lock);
	if (via->polling == 0 || via_chan_active(via) == 0) {
		snd_mtxunlock(via->lock);
		return;
	}

	for (i = 0; i < NDXSCHANS + NMSGDCHANS; i++)
		ptrigger |= (via_poll_channel(&via->pch[i]) != 0) ?
		    (1 << i) : 0;

	for (i = 0; i < NWRCHANS; i++)
		rtrigger |= (via_poll_channel(&via->rch[i]) != 0) ?
		    (1 << i) : 0;

	/* XXX */
	callout_reset(&via->poll_timer, 1/*via->poll_ticks*/,
	    via_poll_callback, via);

	snd_mtxunlock(via->lock);

	for (i = 0; i < NDXSCHANS + NMSGDCHANS; i++) {
		if (ptrigger & (1 << i))
			chn_intr(via->pch[i].channel);
	}
	for (i = 0; i < NWRCHANS; i++) {
		if (rtrigger & (1 << i))
			chn_intr(via->rch[i].channel);
	}
}