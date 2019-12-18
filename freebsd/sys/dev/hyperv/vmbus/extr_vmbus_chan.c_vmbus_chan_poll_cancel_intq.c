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
struct vmbus_channel {scalar_t__ ch_poll_intvl; int /*<<< orphan*/  ch_poll_task; int /*<<< orphan*/  ch_tq; int /*<<< orphan*/  ch_poll_timeo; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_cancel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
vmbus_chan_poll_cancel_intq(struct vmbus_channel *chan)
{

	if (chan->ch_poll_intvl == 0) {
		/* Not enabled. */
		return (false);
	}

	/*
	 * Stop polling callout, so that channel polling task
	 * will not be enqueued anymore.
	 */
	callout_drain(&chan->ch_poll_timeo);

	/*
	 * Disable polling by resetting polling interval.
	 *
	 * NOTE:
	 * The polling interval resetting MUST be conducted
	 * after the callout is drained; mainly to keep the
	 * proper assertion in place.
	 */
	chan->ch_poll_intvl = 0;

	/*
	 * NOTE:
	 * At this point, this channel polling task will not be
	 * enqueued by the callout anymore, time to cancel the
	 * pending one.
	 */
	taskqueue_cancel(chan->ch_tq, &chan->ch_poll_task, NULL);

	/* Polling was enabled. */
	return (true);
}