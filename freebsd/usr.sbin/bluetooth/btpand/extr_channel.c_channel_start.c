#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ pkthdr_t ;
struct TYPE_9__ {int oactive; scalar_t__ qlen; int (* send ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pktlist; int /*<<< orphan*/  wr_ev; } ;
typedef  TYPE_2__ channel_t ;

/* Variables and functions */
 TYPE_1__* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel_close (TYPE_2__*) ; 
 int /*<<< orphan*/  channel_timeout (TYPE_2__*,int) ; 
 int event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  pkthdr_free (TYPE_1__*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
channel_start(int fd, short ev, void *arg)
{
	channel_t *chan = arg;
	pkthdr_t *ph;

	chan->oactive = true;

	while (chan->qlen > 0) {
		ph = STAILQ_FIRST(&chan->pktlist);

		channel_timeout(chan, 10);
		if (chan->send(chan, ph->data) == false) {
			if (event_add(&chan->wr_ev, NULL) == -1) {
				log_err("Could not add channel write event: %m");
				channel_close(chan);
			}
			return;
		}

		STAILQ_REMOVE_HEAD(&chan->pktlist, next);
		pkthdr_free(ph);
		chan->qlen--;
	}

	channel_timeout(chan, 0);
	chan->oactive = false;
}