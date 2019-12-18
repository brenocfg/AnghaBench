#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty {int t_state; TYPE_2__* t_sc; } ;
struct TYPE_5__ {int /*<<< orphan*/  chan; TYPE_1__* board; } ;
typedef  TYPE_2__ drv_t ;
typedef  int /*<<< orphan*/  bdrv_t ;
struct TYPE_4__ {int /*<<< orphan*/ * sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX_DEBUG2 (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  CX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CX_UNLOCK (int /*<<< orphan*/ *) ; 
 int TS_BUSY ; 
 int /*<<< orphan*/  cx_transmitter_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void cx_stop (struct tty *tp, int flag)
{
	drv_t *d;
	bdrv_t *bd;
	int s;

	d = tp->t_sc;
	bd = d->board->sys;
	
	s = splhigh ();
	CX_LOCK (bd);
	if (tp->t_state & TS_BUSY) {
		/* Stop transmitter */
		CX_DEBUG2 (d, ("cx_stop\n"));
		cx_transmitter_ctl (d->chan, 0);
	}
	CX_UNLOCK (bd);
	splx (s);
}