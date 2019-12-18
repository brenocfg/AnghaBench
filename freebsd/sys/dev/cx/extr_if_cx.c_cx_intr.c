#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  ifp; int /*<<< orphan*/  queue; int /*<<< orphan*/  running; } ;
typedef  TYPE_2__ drv_t ;
struct TYPE_12__ {size_t num; TYPE_1__* chan; } ;
typedef  TYPE_3__ cx_board_t ;
struct TYPE_13__ {TYPE_3__* board; } ;
typedef  TYPE_4__ bdrv_t ;
struct TYPE_10__ {TYPE_2__* sys; scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  CX_UNLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  IF_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int NCHAN ; 
 scalar_t__ _IF_QLEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  cx_int_handler (TYPE_3__*) ; 
 int /*<<< orphan*/  cx_led (TYPE_3__*,int) ; 
 int /*<<< orphan*/  cx_led_off ; 
 int hz ; 
 int /*<<< orphan*/ * led_timo ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  sppp_input (int /*<<< orphan*/ ,struct mbuf*) ; 

__attribute__((used)) static void cx_intr (void *arg)
{
	bdrv_t *bd = arg;
	cx_board_t *b = bd->board;
#ifndef NETGRAPH
	int i;
#endif
	int s = splhigh ();

	CX_LOCK (bd);
	/* Turn LED on. */
	cx_led (b, 1);

	cx_int_handler (b);

	/* Turn LED off 50 msec later. */
	callout_reset (&led_timo[b->num], hz/20, cx_led_off, b);
	CX_UNLOCK (bd);
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