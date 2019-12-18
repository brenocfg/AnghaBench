#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ refcnt; scalar_t__ state; scalar_t__ qlen; struct TYPE_5__* sendbuf; struct TYPE_5__* mfilter; struct TYPE_5__* pfilter; int /*<<< orphan*/  pktlist; } ;
typedef  TYPE_1__ channel_t ;

/* Variables and functions */
 scalar_t__ CHANNEL_CLOSED ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  channel_count ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int /*<<< orphan*/  next ; 
 scalar_t__ server_limit ; 
 int /*<<< orphan*/  server_update (int /*<<< orphan*/ ) ; 

void
channel_free(channel_t *chan)
{

	assert(chan->refcnt == 0);
	assert(chan->state == CHANNEL_CLOSED);
	assert(chan->qlen == 0);
	assert(STAILQ_EMPTY(&chan->pktlist));

	LIST_REMOVE(chan, next);
	free(chan->pfilter);
	free(chan->mfilter);
	free(chan->sendbuf);
	free(chan);

	server_update(--channel_count);

	if (server_limit == 0) {
		log_info("connection closed, exiting");
		exit(EXIT_SUCCESS);
	}
}