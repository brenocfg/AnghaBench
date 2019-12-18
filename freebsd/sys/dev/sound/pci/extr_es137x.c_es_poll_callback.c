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
struct es_info {scalar_t__ polling; TYPE_1__* ch; int /*<<< orphan*/  poll_timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  ES_LOCK (struct es_info*) ; 
 int ES_NCHANS ; 
 int /*<<< orphan*/  ES_UNLOCK (struct es_info*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct es_info*) ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 scalar_t__ es_chan_active (struct es_info*) ; 
 scalar_t__ es_poll_channel (TYPE_1__*) ; 

__attribute__((used)) static void
es_poll_callback(void *arg)
{
	struct es_info *es = arg;
	uint32_t trigger = 0;
	int i;

	if (es == NULL)
		return;

	ES_LOCK(es);
	if (es->polling == 0 || es_chan_active(es) == 0) {
		ES_UNLOCK(es);
		return;
	}

	for (i = 0; i < ES_NCHANS; i++) {
		if (es_poll_channel(&es->ch[i]) != 0)
			trigger |= 1 << i;
	}

	/* XXX */
	callout_reset(&es->poll_timer, 1/*es->poll_ticks*/,
	    es_poll_callback, es);

	ES_UNLOCK(es);

	for (i = 0; i < ES_NCHANS; i++) {
		if (trigger & (1 << i))
			chn_intr(es->ch[i].channel);
	}
}