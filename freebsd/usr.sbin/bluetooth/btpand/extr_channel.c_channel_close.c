#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pkthdr_t ;
struct TYPE_4__ {scalar_t__ state; scalar_t__ refcnt; int /*<<< orphan*/ * pfh; int /*<<< orphan*/  qlen; int /*<<< orphan*/  pktlist; scalar_t__ tick; int /*<<< orphan*/  fd; int /*<<< orphan*/  wr_ev; int /*<<< orphan*/  rd_ev; } ;
typedef  TYPE_1__ channel_t ;

/* Variables and functions */
 scalar_t__ CHANNEL_CLOSED ; 
 int /*<<< orphan*/ * STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  channel_free (TYPE_1__*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  pidfile_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkthdr_free (int /*<<< orphan*/ *) ; 

void
channel_close(channel_t *chan)
{
	pkthdr_t *ph;

	assert(chan->state != CHANNEL_CLOSED);

	log_debug("(fd#%d)", chan->fd);

	chan->state = CHANNEL_CLOSED;
	event_del(&chan->rd_ev);
	event_del(&chan->wr_ev);
	close(chan->fd);
	chan->refcnt--;
	chan->tick = 0;

	while ((ph = STAILQ_FIRST(&chan->pktlist)) != NULL) {
		STAILQ_REMOVE_HEAD(&chan->pktlist, next);
		pkthdr_free(ph);
		chan->qlen--;
	}

	if (chan->pfh != NULL) {
		pidfile_remove(chan->pfh);
		chan->pfh = NULL;
	}

	if (chan->refcnt == 0)
		channel_free(chan);
}