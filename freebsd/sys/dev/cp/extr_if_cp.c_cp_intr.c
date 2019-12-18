#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  ifp; int /*<<< orphan*/  queue; int /*<<< orphan*/  running; } ;
typedef  TYPE_2__ drv_t ;
struct TYPE_13__ {size_t num; TYPE_1__* chan; int /*<<< orphan*/ * sys; } ;
typedef  TYPE_3__ cp_board_t ;
struct TYPE_14__ {TYPE_3__* board; } ;
typedef  TYPE_4__ bdrv_t ;
struct TYPE_11__ {TYPE_2__* sys; scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  CP_UNLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  IF_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int NCHAN ; 
 scalar_t__ _IF_QLEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ cp_destroy ; 
 int /*<<< orphan*/  cp_interrupt (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_interrupt_poll (TYPE_3__*,int) ; 
 int /*<<< orphan*/  cp_led (TYPE_3__*,int) ; 
 int /*<<< orphan*/  cp_led_off ; 
 int hz ; 
 int /*<<< orphan*/ * led_timo ; 
 int splimp () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  sppp_input (int /*<<< orphan*/ ,struct mbuf*) ; 

__attribute__((used)) static void cp_intr (void *arg)
{
	bdrv_t *bd = arg;
	cp_board_t *b = bd->board;
#ifndef NETGRAPH
	int i;
#endif
	int s = splimp ();
	if (cp_destroy) {
		splx (s);
		return;
	}
	CP_LOCK (bd);
	/* Check if we are ready */
	if (b->sys == NULL) {
		/* Not we are not, just cleanup. */
		cp_interrupt_poll (b, 1);
		CP_UNLOCK (bd);
		return;
	}
	/* Turn LED on. */
	cp_led (b, 1);

	cp_interrupt (b);

	/* Turn LED off 50 msec later. */
	callout_reset (&led_timo[b->num], hz/20, cp_led_off, b);
	CP_UNLOCK (bd);
	splx (s);

#ifndef NETGRAPH
	/* Pass packets in a lock-free state */
	for (i = 0; i < NCHAN && b->chan[i].type; i++) {
		drv_t *d = b->chan[i].sys;
		struct mbuf *m;
		if (!d || !d->running)
			continue;
		while (_IF_QLEN(&d->queue)) {
			IF_DEQUEUE (&d->queue,m);
			if (!m)
				continue;
			sppp_input (d->ifp, m);	
		}
	}
#endif
}