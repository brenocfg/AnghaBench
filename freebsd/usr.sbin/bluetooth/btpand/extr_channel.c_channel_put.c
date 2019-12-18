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
typedef  int /*<<< orphan*/  packet_t ;
struct TYPE_4__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  oactive; int /*<<< orphan*/  pktlist; int /*<<< orphan*/  qlen; } ;
typedef  TYPE_1__ channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  EV_WRITE ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/ * pkthdr_alloc (int /*<<< orphan*/ *) ; 

void
channel_put(channel_t *chan, packet_t *pkt)
{
	pkthdr_t *ph;

	ph = pkthdr_alloc(pkt);
	if (ph == NULL)
		return;

	chan->qlen++;
	STAILQ_INSERT_TAIL(&chan->pktlist, ph, next);

	if (!chan->oactive)
		channel_start(chan->fd, EV_WRITE, chan);
}